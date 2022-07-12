/** @file PrehistoryLevel.cpp */
#include "Objects/Levels/PrehistoryLevel.h"
#include "Objects/Nodes/SpriteNode.h"
#include "Objects/Nodes/MoneyNode.h"
#include "Objects/Nodes/HeartNode.h"

PrehistoryLevel::PrehistoryLevel(Context& context, PlayerInfo& playerInfo, unsigned int numLevel)
: Level(context, playerInfo, numLevel)
{
    buildScene();
}

LevelID::ID PrehistoryLevel::nextLevel() const
{
    return LevelID::FirstLevel;
}

void PrehistoryLevel::buildScene()
{
    auto* backgroundLayer = Level::getLayer(Level::Background);
    auto* floorLayer = Level::getLayer(Level::Floor);
    auto& context = Level::getContext();

    //Background
    const sf::Texture& texture = context.textures.get(TexturesID::PrehistoryLevel);
    std::unique_ptr<SpriteNode> background(new SpriteNode(texture));
    background->setPosition(420.f, 0.f);
    backgroundLayer->attachChild(std::move(background));

    std::unique_ptr<Door> door2(new Door(Level::getContext(), true));
    door2->setPosition({960, 1039});
    door2->setRotation(180);
    floorLayer->attachChild(std::move(door2));

    std::unique_ptr<HeartNode> test(new HeartNode(context, 20));
    test->setPosition({600, 500});
    floorLayer->attachChild(std::move(test));

    std::unique_ptr<MoneyNode> test2(new MoneyNode(context, 5));
    test2->setPosition({1000, 300});
    floorLayer->attachChild(std::move(test2));
}
