/** @file Map.cpp */
#include "Objects/Map.h"
#include "Objects/Levels/PrehistoryLevel.h"

Map::Map(Context& context)
: mContext(context)
, mLevel(nullptr)
, mNumLevel(0)
, mPlayerInfo({100, 0})
{
    registerLevels();
    createLevel();
}

CommandQueue& Map::getCommandQueue()
{
    return mLevel->getCommandQueue();
}

void Map::update(sf::Time dt)
{
    mLevel->update(dt);
    if (mLevel->isFinished())
    {
        mNumLevel++;
        createLevel();
    }
}

void Map::draw()
{
    mLevel->draw();
}

void Map::registerLevels()
{
    registerLevel<PrehistoryLevel>(LevelID::Prehistory);
}

void Map::createLevel()
{
    mLevel = mFactories[mNumLevel % LevelID::LevelCount]();
}
