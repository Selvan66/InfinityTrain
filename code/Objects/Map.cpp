/** @file Map.cpp */
#include "Objects/Map.h"
#include "Objects/Levels/PrehistoryLevel.h"

Map::Map(Context& context)
: mContext(context)
, mLevel(nullptr)
, mNumLevel(0)
, mStartTime(context.statistics.get(Statistics::TimePlay))
, mTimerText("", context.fonts.get(FontsID::PixelFont), 50u)
, mPlayerInfo({90, 0})
, mPlayerInfoGui(context, mPlayerInfo)
{
    registerLevels();
    createLevel();

    mTimerText.setFillColor(sf::Color::White);
    mTimerText.setOutlineColor(sf::Color::Black);
    mTimerText.setOutlineThickness(2.f);
    mTimerText.setPosition({10, 40});

    mPlayerInfoGui.setCharacterSize(50u);
    mPlayerInfoGui.setPosition({5, 900});
}

CommandQueue& Map::getCommandQueue()
{
    return mLevel->getCommandQueue();
}

void Map::update(sf::Time dt)
{
    mTimerText.setString("Time: " + Utility::timeToString((mContext.statistics.get(Statistics::TimePlay) - mStartTime)/1000));
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
    mContext.window.draw(mTimerText);
}

void Map::registerLevels()
{
    registerLevel<PrehistoryLevel>(LevelID::Prehistory);
}

void Map::createLevel()
{
    mLevel = mFactories[mNumLevel % LevelID::LevelCount]();
}
