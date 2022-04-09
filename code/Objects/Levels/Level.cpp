/** @file Level.cpp */
#include "Objects/Levels/Level.h"
#include "Objects/Nodes/SpriteNode.h"

Level::Level(Context& context, unsigned int levelNum)
: mContext(context)
, mLevelNum(levelNum)
, mLevelNumText(std::to_string(levelNum), context.fonts.get(FontsID::PixelFont), 400)
, mLevelBounds(460.f, 80.f, 1000.f, 1000.f)
, mSceneLayer()
{
    buildScene();
    mLevelNumText.setFillColor(sf::Color::Black);
}

sf::FloatRect Level::getLevelBounds() const
{
    return mLevelBounds;
}

void Level::update(sf::Time dt, CommandQueue& commands)
{
    mSceneGraph.update(dt, commands);
}

void Level::draw()
{
    auto& window = mContext.window;
    window.draw(mSceneGraph);
    window.draw(mLevelNumText);
}

Context& Level::getContext() const
{
    return mContext;
}

unsigned int Level::getLevelNum() const
{
    return mLevelNum;
}

void Level::buildScene()
{
    for (int i = 0; i < LayerCount; ++i)
    {
        Category::Type category = (i == Battlefield) ? Category::Battlefield : Category::None;

        SceneNode::Ptr layer(new SceneNode(category));
        mSceneLayer[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    //Background
    const sf::Texture& texture = mContext.textures.get(TexturesID::DefaultLevel);
    std::unique_ptr<SpriteNode> background(new SpriteNode(texture));
    background->setPosition(420.f, 0.f);
    mSceneLayer[Background]->attachChild(std::move(background));
}
