/** @file Level.cpp */
#include "Objects/Levels/Level.h"

Level::Level(Context& context)
: mContext(context)
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
        mSceneGraph.onCommand(mCommands.pop(), dt);

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

SceneNode* Level::getLayer(Layer layer) const
{
    return mSceneLayer[layer];
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
}
