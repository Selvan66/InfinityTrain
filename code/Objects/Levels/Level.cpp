/** @file Level.cpp */
#include "Objects/Levels/Level.h"

Level::Level(LvlContext& lvlContext)
  : mLvlContext(lvlContext), mCommands(), mSceneGraph(), mSceneLayer(),
    mPlayerNode(nullptr) {
  buildScene();
}

CommandQueue& Level::getCommandQueue() { return mCommands; }

void Level::draw() {
  auto& window = mLvlContext.context.window;
  window.draw(mSceneGraph);
}

bool Level::isPlayerAlive() const {
  if (mPlayerNode != nullptr)
    return !mPlayerNode->isDestroyed();
  return false;
}

void Level::update(sf::Time dt) {
  mLvlContext.context.statistics.increase(
    Statistics::TimePlay, static_cast<unsigned long long>(dt.asMilliseconds()));

  mSceneGraph.removeObjects();
  mSceneGraph.update(dt, mCommands);

  while (!mCommands.isEmpty())
    mSceneGraph.onCommand(mCommands.pop(), dt);

  updatePlayer(mPlayerNode);
  destoryEntitiesOutsideLevel();
}

LevelID::ID Level::nextLevel() const { return LevelID::None; }

const sf::FloatRect Level::getLevelBounds() {
  return sf::FloatRect(500.f, 80.f, 920.f, 920.f);
}

bool Level::isFinished() const {
  return mSceneLayer[Battlefield]->getChildrenSize() == 1;
}

SceneNode* Level::getLayer(Layer layer) const { return mSceneLayer[layer]; }

LvlContext& Level::getLvlContext() const { return mLvlContext; }

void Level::setPlayerPos(sf::Vector2f pos) {
  assert(mPlayerNode != nullptr);
  mPlayerNode->setPosition(pos);
}

void Level::buildScene() {
  for (size_t i = 0; i < LayerCount; ++i) {
    Category::Type category = Category::None;

    switch (static_cast<Layer>(i)) {
    case Battlefield:
      category = Category::Battlefield;
      break;
    case Floor:
      category = Category::Floor;
      break;
    default:
      category = Category::None;
      break;
    }

    SceneNode::Ptr layer(new SceneNode(category));
    mSceneLayer[i] = layer.get();

    mSceneGraph.attachChild(std::move(layer));
  }

  std::unique_ptr<PlayerNode> playerNode(
    new PlayerNode(mLvlContext.context, Level::getLvlContext().playerInfo));
  mPlayerNode = playerNode.get();
  mSceneLayer[Battlefield]->attachChild(std::move(playerNode));
}

void Level::adaptNodesPosition(SceneNode* node) {
  sf::FloatRect bounds = getLevelBounds();
  sf::Vector2f position = node->getWorldPosition();
  sf::FloatRect size = node->getBoundingRect();

  position.x = std::max(position.x, bounds.left + size.width / 2.f);
  position.x =
    std::min(position.x, bounds.left + bounds.width - size.width / 2.f);
  position.y = std::max(position.y, bounds.top - size.height / 4.f);
  position.y =
    std::min(position.y, bounds.top + bounds.height - size.height / 2.f);

  node->setPosition(position);
}

void Level::updatePlayer(PlayerNode* player) {
  adaptNodesPosition(player);

  mLvlContext.playerInfo.backpack.drop(player->getWorldPosition(),
                                       *mSceneLayer[Floor]);
  mLvlContext.playerInfo.backpack.action(*player);
}

void Level::destoryEntitiesOutsideLevel() {
  Command command;
  command.category = Category::AlliedProjectile | Category::EnemyProjectile;
  command.action = derivedAction<Entity>([](Entity& e, sf::Time) {
    if (!getLevelBounds().intersects(e.getBoundingRect())) {
      e.destroy();
    }
  });

  mCommands.push(command);
}
