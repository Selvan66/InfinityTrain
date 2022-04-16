/** @file PrehistoryLevel.cpp */
#include "Objects/Levels/PrehistoryLevel.h"
#include "Objects/Nodes/SpriteNode.h"

PrehistoryLevel::PrehistoryLevel(Context& context)
: Level(context)
{
    buildScene();
}

void PrehistoryLevel::buildScene()
{
    auto* backgroundLayer = Level::getLayer(Level::Background);
    auto& context = Level::getContext();

    //Background
    const sf::Texture& texture = mContext.textures.get(TexturesID::PrehistoryLevel);
    std::unique_ptr<SpriteNode> background(new SpriteNode(texture));
    background->setPosition(420.f, 0.f);
    backgroundLayer->attachChild(std::move(background));

}
