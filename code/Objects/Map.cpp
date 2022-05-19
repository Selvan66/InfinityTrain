/** @file Map.cpp */
#include "Objects/Map.h"
#include "Objects/Levels/PrehistoryLevel.h"

Map::Map(Context& context)
: mContext(context)
, mLevel(nullptr)
, mNumLevel(0)
, mPlayerInfo({90, 0})
, mPlayerInfoGui(context, mPlayerInfo)
{
    registerLevels();
    createLevel();

    mPlayerInfoGui.setCharacterSize(50u);
    mPlayerInfoGui.setPosition({5, 900});
}

CommandQueue& Map::getCommandQueue()
{
    return mLevel->getCommandQueue();
}

void Map::update(sf::Time dt)
{
    mLevel->update(dt);
    mPlayerInfoGui.update(dt);
    if (mLevel->isFinished())
    {
        mNumLevel++;
        createLevel();
    }
}

void Map::draw()
{
    mLevel->draw();
    mContext.window.draw(mPlayerInfoGui);
}

void Map::registerLevels()
{
    registerLevel<PrehistoryLevel>(LevelID::Prehistory);
}

void Map::createLevel()
{
    mLevel = mFactories[mNumLevel % LevelID::LevelCount]();
}
