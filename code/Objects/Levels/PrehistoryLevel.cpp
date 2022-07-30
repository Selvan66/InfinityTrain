/** @file PrehistoryLevel.cpp */
#include "Objects/Levels/PrehistoryLevel.h"
#include "Objects/Nodes/SpriteNode.h"
#include "Objects/Nodes/Pickup/Money.h"
#include "Objects/Nodes/Pickup/Potion.h"
#include "Objects/Nodes/Pickup/Heart.h"

PrehistoryLevel::PrehistoryLevel(LvlContext& lvlContext)
: Level(lvlContext)
{
    buildScene();
}

void PrehistoryLevel::update(sf::Time dt)
{
    Level::update(dt);
    Level::updatePlayer(mPlayer);

    if (Level::isFinished())
        mDoor->open();
}

LevelID::ID PrehistoryLevel::nextLevel() const
{
    if (mDoor->isInteract())
        return LevelID::FirstLevel;
    return LevelID::None;
}

void PrehistoryLevel::buildBackground()
{
    auto& context = Level::getLvlContext().context;
    auto* backgroundLayer = Level::getLayer(Level::Background);

    const sf::Texture& texture = context.textures.get(TexturesID::PrehistoryLevel);
    std::unique_ptr<SpriteNode> background(new SpriteNode(texture));
    background->setPosition(420.f, 0.f);
    backgroundLayer->attachChild(std::move(background));
}

void PrehistoryLevel::buildFloor()
{
    auto& context = Level::getLvlContext().context;
    auto* floorLayer = Level::getLayer(Level::Floor);

    std::unique_ptr<Door> door(new Door(context));
    door->setPosition({960, 1039});
    door->setRotation(180);
    mDoor = door.get();
    floorLayer->attachChild(std::move(door));

    std::unique_ptr<Potion> test(new Potion(context, 20));
    test->setPosition({600, 500});
    floorLayer->attachChild(std::move(test));

    std::unique_ptr<Money> test2(new Money(context, 5));
    test2->setPosition({1000, 300});
    floorLayer->attachChild(std::move(test2));

    std::unique_ptr<Heart> test3(new Heart(context, 5));
    test3->setPosition({1200, 400});
    floorLayer->attachChild(std::move(test3));
}

void PrehistoryLevel::buildBattlefield()
{
    auto& context = Level::getLvlContext().context;
    auto* battlefieldLayer = Level::getLayer(Level::Battlefield);
    
    std::unique_ptr<PlayerNode> playerNode(new PlayerNode(context, Level::getLvlContext().playerInfo));
    playerNode->setPosition({960, 540});
    mPlayer = playerNode.get();
    battlefieldLayer->attachChild(std::move(playerNode));
    
}

void PrehistoryLevel::buildScene()
{
    buildBackground();
    buildFloor();
    buildBattlefield();
}
