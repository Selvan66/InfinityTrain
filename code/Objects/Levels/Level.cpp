/** @file Level.cpp */
#include "Objects/Levels/Level.h"

Level::Level(LvlContext& lvlContext)
: mLvlContext(lvlContext)
, mCommands()
, mSceneGraph()
, mSceneLayer()
{ 
    buildScene();
}

CommandQueue& Level::getCommandQueue()
{
    return mCommands;
}

void Level::draw()
{
    auto& window = mLvlContext.context.window;
    window.draw(mSceneGraph);
}

void Level::update(sf::Time dt)
{
    mLvlContext.context.statistics.increase(Statistics::TimePlay, dt.asMilliseconds());

    while (!mCommands.isEmpty())
        mSceneGraph.onCommand(mCommands.pop(), dt);

    mSceneGraph.removeObjects();
    mSceneGraph.update(dt, mCommands);
}

LevelID::ID Level::nextLevel() const
{
    return LevelID::None;
}

bool Level::isFinished() const
{
    return mSceneLayer[Battlefield]->getChildrenSize() == 1;
}

SceneNode* Level::getLayer(Layer layer) const
{
    return mSceneLayer[layer];
}

LvlContext& Level::getLvlContext() const
{
    return mLvlContext;
}

void Level::updatePlayer(PlayerNode* player)
{
    player->setVelocity(0, 0);
    adaptNodesPosition(player);

    mLvlContext.playerInfo.backpack.drop(player->getPosition(), *mSceneLayer[Floor]);
    mLvlContext.playerInfo.backpack.use(*player);
}

void Level::buildScene()
{
    for (int i = 0; i < LayerCount; ++i)
    {
        Category::Type category = Category::None;

        switch (static_cast<Layer>(i))
        {
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
}

void Level::adaptNodesPosition(SceneNode* node)
{
    sf::FloatRect bounds = getLevelBounds();
    sf::Vector2f position = node->getPosition();
    sf::FloatRect size = node->getBoundingRect();

    position.x = std::max(position.x, bounds.left + size.width / 2.f);
    position.x = std::min(position.x, bounds.left + bounds.width - size.width / 2.f);
    position.y = std::max(position.y, bounds.top - size.height / 4.f);
    position.y = std::min(position.y, bounds.top + bounds.height - size.height / 2.f);

    node->setPosition(position);
}

sf::FloatRect Level::getLevelBounds() const
{
    return sf::FloatRect(500.f, 80.f, 920.f, 920.f);
}