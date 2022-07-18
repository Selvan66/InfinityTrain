/** @file StartLevel.cpp */
#include "Objects/Levels/StartLevel.h"
#include "Objects/Nodes/SpriteNode.h"

StartLevel::StartLevel(LvlContext& lvlContext)
: Level(lvlContext)
{
    buildScene();
}

void StartLevel::update(sf::Time dt)
{
    Level::update(dt);
    Level::updatePlayer(mPlayer);

    if (Level::isFinished())
        mDoor->open();
}

LevelID::ID StartLevel::nextLevel() const
{
    if (mDoor->isInteract())
        return LevelID::FirstLevel;
    return LevelID::None;
}

void StartLevel::buildBackground()
{
    auto& context = Level::getLvlContext().context;
    auto* backgroundLayer = Level::getLayer(Level::Background);

    const sf::Texture& texture = context.textures.get(TexturesID::StartLevel);
    std::unique_ptr<SpriteNode> background(new SpriteNode(texture));
    background->setPosition(420.f, 0.f);
    backgroundLayer->attachChild(std::move(background));
}

void StartLevel::buildFloor()
{
    auto& context = Level::getLvlContext().context;
    auto* floorLayer = Level::getLayer(Level::Floor);

    std::unique_ptr<Door> door(new Door(context));
    door->setRotation(90);
    door->setPosition({461, 540});
    mDoor = door.get();
    floorLayer->attachChild(std::move(door));
}

void StartLevel::buildBattlefield()
{
    auto& context = Level::getLvlContext().context;
    auto* battlefieldLayer = Level::getLayer(Level::Battlefield);
    
    std::unique_ptr<PlayerNode> playerNode(new PlayerNode(context, Level::getLvlContext().playerInfo));
    playerNode->setPosition({960, 540});
    mPlayer = playerNode.get();
    battlefieldLayer->attachChild(std::move(playerNode));
}

void StartLevel::buildScene()
{
    buildBackground();
    buildFloor();
    buildBattlefield();    
}
