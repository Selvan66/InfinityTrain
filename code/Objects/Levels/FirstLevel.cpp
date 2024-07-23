/** @file FirstLevel.cpp */
#include "spdlog/spdlog.h"

#include "Objects/Levels/FirstLevel.h"
#include "Objects/Nodes/Pickup/Money.h"
#include "Objects/Nodes/SpriteNode.h"

FirstLevel::FirstLevel(LvlContext& lvlContext) : Level(lvlContext) {
  buildScene();
}

void FirstLevel::update(sf::Time dt) {
  Level::update(dt);

  if (Level::isFinished()) {
    spdlog::debug("FirstLevel::update | isFinished");
    mDoor->open();
  }
}

LevelID::ID FirstLevel::nextLevel() const {
  if (mDoor->isInteract()) {
    spdlog::debug("FirstLevel::nextLevel | Prehistory");
    return LevelID::Prehistory;
  }
  return LevelID::None;
}

void FirstLevel::buildBackground() {
  auto& context = Level::getLvlContext().context;
  auto* backgroundLayer = Level::getLayer(Level::Background);

  const sf::Texture& texture = context.textures.get(TexturesID::FirstLevel);
  std::unique_ptr<SpriteNode> background(new SpriteNode(texture));
  background->setPosition(420.f, 0.f);
  backgroundLayer->attachChild(std::move(background));
}

void FirstLevel::buildFloor() {
  auto& context = Level::getLvlContext().context;
  auto* floorLayer = Level::getLayer(Level::Floor);

  std::unique_ptr<Door> door(new Door(context));
  door->setPosition({1458, 461});
  door->setRotation(270);
  mDoor = door.get();
  floorLayer->attachChild(std::move(door));

  std::unique_ptr<Door> door2(new Door(context));
  door2->setPosition({960, 1039});
  floorLayer->attachChild(std::move(door2));

  for (int i = 0; i < 10; i++) {
    std::unique_ptr<Money> test(new Money(context, 20));
    test->setPosition({(30.f * static_cast<float>(i)) + 500.f, 500.f});
    floorLayer->attachChild(std::move(test));
  }
}

void FirstLevel::buildBattlefield() {
  // auto& context = Level::getLvlContext().context;
  // auto* battlefieldLayer = Level::getLayer(Level::Battlefield);
  Level::setPlayerPos({900.f, 540.f});
}

void FirstLevel::buildScene() {
  buildBackground();
  buildFloor();
  buildBattlefield();
}
