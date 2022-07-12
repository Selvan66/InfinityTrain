/** @file Level.cpp */
#include "Objects/Levels/Level.h"

Level::Level(Context& context, PlayerInfo& playerInfo, unsigned int numLevel)
: mContext(context)
, mPlayerInfo(playerInfo)
, mCommands()
, mLevelBounds(500.f, 80.f, 920.f, 920.f)
, mSceneLayer()
, mPlayer(nullptr)
, mFinished(false)
, mNumLevel(numLevel)
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
    mPlayerInfo.backpack.drop(mPlayer->getPosition(), *mSceneLayer[Floor]);

    if (mSceneLayer[Battlefield]->getChildrenSize() == 1)
        mFinished = true;

    if (mFinished)
        mDoor->open();

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

LevelID::ID Level::nextLevel() const
{
    return LevelID::None;
}

bool Level::isFinished() const
{
    return mFinished;
}

bool Level::isPlayerGoToNextLevel() const
{
    return mDoor->isInteract();
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

PlayerNode* Level::getPlayer() const
{
    return mPlayer;
}

Door* Level::getDoor() const
{
    return mDoor;
}

unsigned int Level::getNumLevel() const
{
    return mNumLevel;
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
        Category::Type category = Category::None;

        switch (static_cast<Layer>(i))
        {
            case Battlefield:
                category = Category::Battlefield;
                break;
            case Floor:
                category = Category::Floor;
                break;
            default:
                category = Category::None;
                break;
        }

        SceneNode::Ptr layer(new SceneNode(category));
        mSceneLayer[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    std::unique_ptr<PlayerNode> player(new PlayerNode(Level::getContext(), mPlayerInfo));
    player->setPosition({960, 998});
    mPlayer = player.get();
    mSceneLayer[Battlefield]->attachChild(std::move(player)); 

    std::unique_ptr<Door> door(new Door(Level::getContext(), false));
    door->setPosition({960, 41});
    mDoor = door.get();
    mSceneLayer[Floor]->attachChild(std::move(door));
}
