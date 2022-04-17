/** @file Map.cpp */
#include "Objects/Map.h"
#include "Objects/Levels/PrehistoryLevel.h"

Map::Map(Context& context)
: mContext(context)
, mLevel(nullptr)
, mNumLevel(1)
{
    registerLevels();
    createLevel();
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
