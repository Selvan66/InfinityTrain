/** @file Level.cpp */
#include "Objects/Levels/Level.h"
#include "Objects/Nodes/MoneyNode.h"
#include "Objects/Nodes/HeartNode.h"

Level::Level(Context& context, PlayerInfo& playerInfo)
: mContext(context)
, mPlayerInfo(playerInfo)
, mCommands()
, mLevelBounds(500.f, 80.f, 920.f, 920.f)
, mSceneLayer()
, mPlayer(nullptr)
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
    mContext.statistics.increase(Statistics::TimePlay, dt.asMilliseconds());


    mPlayer->setVelocity(0, 0);
    while (!mCommands.isEmpty())
        mSceneGraph.onCommand(mCommands.pop(), dt);

    mSceneGraph.removeObjects();
    mSceneGraph.update(dt, mCommands);

    adaptNodesPosition(mPlayer);
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

void Level::adaptNodesPosition(SceneNode* node)
{
    sf::FloatRect bounds = getLevelBounds();
    sf::Vector2f position = node->getPosition();
    sf::FloatRect size = node->getBoundingRect();

    position.x = std::max(position.x, bounds.left + size.width / 2.f);
    position.x = std::min(position.x, bounds.left + bounds.width - size.width / 2.f);
    position.y = std::max(position.y, bounds.top - size.height / 4.f);
    position.y = std::min(position.y, bounds.top + bounds.height - size.height / 2.f);

    node->setPosition(position);
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

    std::unique_ptr<PlayerNode> player(new PlayerNode(Level::getContext(), mPlayerInfo));
    player->setPosition(900, 500);
    mPlayer = player.get();
    mSceneLayer[Battlefield]->attachChild(std::move(player)); 

    std::unique_ptr<HeartNode> test(new HeartNode(mContext, 20));
    test->setPosition({600, 500});
    mSceneLayer[Floor]->attachChild(std::move(test));

    std::unique_ptr<MoneyNode> test2(new MoneyNode(mContext, 5));
    test2->setPosition({1000, 300});
    mSceneLayer[Floor]->attachChild(std::move(test2));
}
