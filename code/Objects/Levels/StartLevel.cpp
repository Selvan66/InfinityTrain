/** @file StartLevel.cpp */
#include "spdlog/spdlog.h"

#include "Objects/Levels/StartLevel.h"
#include "Objects/Nodes/SpriteNode.h"

StartLevel::StartLevel(LvlContext& lvlContext) : Level(lvlContext) {
  buildScene();
}

void StartLevel::update(sf::Time dt) {
  Level::update(dt);

  if (Level::isFinished()) {
    mDoor->open();
  }
}

LevelID::ID StartLevel::nextLevel() const {
  if (mDoor->isInteract()) {
    spdlog::debug("StartLevel::nextLevel | FirstLevel");
    return LevelID::FirstLevel;
  }
  return LevelID::None;
}

void StartLevel::buildBackground() {
  auto& context = Level::getLvlContext().context;
  auto* backgroundLayer = Level::getLayer(Level::Background);

  const sf::Texture& texture = context.textures.get(TexturesID::StartLevel);
  std::unique_ptr<SpriteNode> background(new SpriteNode(texture));
  background->setPosition(420.f, 0.f);
  backgroundLayer->attachChild(std::move(background));
}

void StartLevel::buildFloor() {
  auto& context = Level::getLvlContext().context;
  auto* floorLayer = Level::getLayer(Level::Floor);

  std::unique_ptr<Door> door(new Door(context));
  door->setRotation(90);
  door->setPosition({461, 540});
  mDoor = door.get();
  floorLayer->attachChild(std::move(door));
}

void StartLevel::buildBattlefield() {
  // auto& context = Level::getLvlContext().context;
  // auto* battlefieldLayer = Level::getLayer(Level::Battlefield);

  Level::setPlayerPos({900.f, 540.f});
}

void StartLevel::buildScene() {
  buildBackground();
  buildFloor();
  buildBattlefield();
}
