/** @file Map.cpp */
#include "Objects/Map.h"
#include "Objects/Levels/PrehistoryLevel.h"

Map::Map(Context& context)
: mContext(context)
, mLevel(nullptr)
, mNumLevel(0)
, mStartTime(context.statistics.get(Statistics::TimePlay))
, mTimerText("", context.fonts.get(FontsID::PixelFont), 50u)
, mPlayerInfo(context)
{
    registerLevels();
    createLevel();

    mTimerText.setFillColor(sf::Color::White);
    mTimerText.setOutlineColor(sf::Color::Black);
    mTimerText.setOutlineThickness(2.f);
    mTimerText.setPosition({10, 40});

    mPlayerInfo.stats.setPosition({150, 300});
    mPlayerInfo.backpack.setPosition({1650, 600});
}

void Map::update(sf::Time dt)
{
    auto& commands = mLevel->getCommandQueue();
    mContext.player.handleRealtimeInput(commands);

    mTimerText.setString("Time: " + Utility::timeToString((mContext.statistics.get(Statistics::TimePlay) - mStartTime)/1000));
    mLevel->update(dt);
    if (mLevel->isFinished())
    {
        mNumLevel++;
        createLevel();
    }

    mPlayerInfo.backpack.update();
}

void Map::handleEvent(const sf::Event& event)
{
    auto& commands = mLevel->getCommandQueue();
    mContext.player.handleEvent(event, commands);
    mPlayerInfo.backpack.handleEvent(event);
}

void Map::draw()
{
    mLevel->draw();
    mContext.window.draw(mTimerText);
    mContext.window.draw(mPlayerInfo.stats);
    mContext.window.draw(mPlayerInfo.backpack);
}

void Map::registerLevels()
{
    registerLevel<PrehistoryLevel>(LevelID::Prehistory);
}

void Map::createLevel()
{
    mLevel = mFactories[mNumLevel % LevelID::LevelCount]();
}
