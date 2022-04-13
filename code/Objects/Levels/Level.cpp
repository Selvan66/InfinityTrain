/** @file Level.cpp */
#include "Objects/Levels/Level.h"
#include "Objects/Nodes/SpriteNode.h"

Level::Level(Context& context, Player& player)
: mContext(context)
, mPlayer(player)
, mCommands()
, mLevelBounds(460.f, 80.f, 1000.f, 1000.f)
, mSceneLayer()
, mFinished(false)
{
    buildScene();
}

sf::FloatRect Level::getLevelBounds() const
{
    return mLevelBounds;
}

void Level::update(sf::Time dt)
{
    while (!mCommands.isEmpty())
    {
        mSceneGraph.onCommand(mCommands.pop(), dt);
    }
    mSceneGraph.update(dt, mCommands);
}

void Level::draw()
{
    auto& window = mContext.window;
    window.draw(mSceneGraph);
}

bool Level::isFinished() const
{
    return mFinished;
}

Context& Level::getContext() const
{
    return mContext;
}

CommandQueue& Level::getCommandQueue()
{
    return mCommands;
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
