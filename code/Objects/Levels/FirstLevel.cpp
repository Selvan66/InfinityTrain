/** @file FirstLevel.cpp */
#include "Objects/Levels/FirstLevel.h"
#include "Objects/Nodes/SpriteNode.h"
#include "Objects/Nodes/MoneyNode.h"

FirstLevel::FirstLevel(Context& context, PlayerInfo& playerInfo, unsigned int numLevel)
: Level(context, playerInfo, numLevel)
{
    buildScene();
}

LevelID::ID FirstLevel::nextLevel() const
{
    return LevelID::Prehistory;
}

void FirstLevel::buildScene()
{
    // Player and exit door
    auto numLevel = Level::getNumLevel();

    auto* player = Level::getPlayer();
    if (numLevel == 1)
        player->setPosition({1417, 461});

    auto* backgroundLayer = Level::getLayer(Level::Background);
    auto& context = Level::getContext();

    //Background
    const sf::Texture& texture = context.textures.get(TexturesID::FirstLevel);
    std::unique_ptr<SpriteNode> background(new SpriteNode(texture));
    background->setPosition(420.f, 0.f);
    backgroundLayer->attachChild(std::move(background)); 

    // Floor
    auto* floorLayer = Level::getLayer(Level::Floor);

    std::unique_ptr<Door> door(new Door(Level::getContext(), true));
    door->setPosition({1458, 461});
    door->setRotation(270);
    floorLayer->attachChild(std::move(door));

    std::unique_ptr<Door> door2(new Door(Level::getContext(), true));
    door2->setPosition({960, 1039});
    floorLayer->attachChild(std::move(door2));

    for (int i = 0; i < 10; i++)
    {
        std::unique_ptr<MoneyNode> test(new MoneyNode(context, 20));
        test->setPosition({(30.f * i) + 500.f, 500.f});
        floorLayer->attachChild(std::move(test));
    }
}
