/** @file StartLevel.cpp */
#include "Objects/Levels/StartLevel.h"
#include "Objects/Nodes/SpriteNode.h"

StartLevel::StartLevel(Context& context, PlayerInfo& playerInfo, unsigned int numLevel)
: Level(context, playerInfo, numLevel)
{
    buildScene();
}

LevelID::ID StartLevel::nextLevel() const
{
    return LevelID::FirstLevel;
}

void StartLevel::buildScene()
{
    // Player and exit door
    auto* player = Level::getPlayer();
    player->setPosition({960, 540});

    auto* door = Level::getDoor();
    door->setRotation(90);
    door->setPosition({461, 540});

    auto* backgroundLayer = Level::getLayer(Level::Background);
    auto& context = Level::getContext();

    //Background
    const sf::Texture& texture = context.textures.get(TexturesID::StartLevel);
    std::unique_ptr<SpriteNode> background(new SpriteNode(texture));
    background->setPosition(420.f, 0.f);
    backgroundLayer->attachChild(std::move(background));
}
