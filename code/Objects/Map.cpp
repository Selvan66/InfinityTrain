/** @file Map.cpp */
#include "Objects/Map.h"
#include "Objects/Levels/PrehistoryLevel.h"
#include "Objects/Levels/StartLevel.h"
#include "Objects/Levels/FirstLevel.h"
#include "Gui/Text.h"

#include <iostream>

Map::Map(Context& context)
: mContext(context)
, mLevel(nullptr)
, mNumLevel(0)
, mStartTime(context.statistics.get(Statistics::TimePlay))
, mGui()
, mPlayerInfo(context)
{
    registerLevels();
    mLevel = mFactories[LevelID::StartLevel]();

    sf::Vector2f window_size = sf::Vector2f(mContext.window.getView().getSize());
    ParserGui parser = context.gui.get(GuiFileID::Map);
    parser.addConst("WINDOW_WIDTH", window_size.x);
    parser.addConst("TEXT_HEIGHT", 70.f);
    mGui = parser.parse(context);

    mPlayerInfo.stats.setPosition({window_size.x / 9, 300});
    mPlayerInfo.backpack.setPosition({(window_size.x * 8 / 9) - 100, 600});
}

void Map::update(sf::Time dt)
{
    auto& commands = mLevel->getCommandQueue();
    mContext.player.handleRealtimeInput(commands);

    Utility::safeCasting<Text>(mGui->at("timer").get())->setString("Time: " + Utility::timeToString((mContext.statistics.get(Statistics::TimePlay) - mStartTime)/1000));
    mLevel->update(dt);
    if (mLevel->isPlayerGoToNextLevel())
    {
        mNumLevel++;
        Utility::safeCasting<Text>(mGui->at("level").get())->setString("Level: " + std::to_string(mNumLevel));
        mLevel = mFactories[mLevel->nextLevel()]();
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
    for (auto& component : *mGui)
			mContext.window.draw(*component.second);
    mLevel->draw();
    mContext.window.draw(mPlayerInfo.stats);
    mContext.window.draw(mPlayerInfo.backpack);
}

void Map::registerLevels()
{
    registerLevel<PrehistoryLevel>(LevelID::Prehistory);
    registerLevel<StartLevel>(LevelID::StartLevel);
    registerLevel<FirstLevel>(LevelID::FirstLevel);
}
