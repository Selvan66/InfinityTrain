/** @file Map.cpp */
#include "Objects/Map.h"
#include "Objects/Levels/PrehistoryLevel.h"
#include "Objects/Levels/StartLevel.h"
#include "Objects/Levels/FirstLevel.h"
#include "Gui/Text.h"

Map::Map(Context& context)
: mLvlContext{context, PlayerInfo(context), 0}
, mLevel(nullptr)
, mStartTime(context.statistics.get(Statistics::TimePlay))
, mGui()
{
    registerLevels();
    mLevel = mFactories[LevelID::StartLevel]();

    sf::Vector2f window_size = sf::Vector2f(context.window.getView().getSize());
    ParserGui parser = context.gui.get(GuiFileID::Map);
    parser.addConst("WINDOW_WIDTH", window_size.x);
    parser.addConst("TEXT_HEIGHT", 70.f);
    mGui = parser.parse(context);

    mLvlContext.playerInfo.stats.setPosition({window_size.x / 9, 300});
    mLvlContext.playerInfo.backpack.setPosition({(window_size.x * 8 / 9) - 100, 600});
    mLvlContext.playerInfo.equipment.setPosition({(window_size.x * 8 / 9) - 20, 200});
}

void Map::update(sf::Time dt)
{
    auto& commands = mLevel->getCommandQueue();
    auto& context = mLvlContext.context;

    context.player.handleRealtimeInput(commands);
    mLvlContext.playerInfo.backpack.update();
    mLvlContext.playerInfo.equipment.update();

    Utility::safeCasting<Text>(mGui->at("timer").get())->setString("Time: " + Utility::timeToString((context.statistics.get(Statistics::TimePlay) - mStartTime)/1000));
    
    mLevel->update(dt);
    if (mLevel->nextLevel() != LevelID::None)
    {
        mLvlContext.numLevel++;
        Utility::safeCasting<Text>(mGui->at("level").get())->setString("Level: " + std::to_string(mLvlContext.numLevel));
        mLevel = mFactories[mLevel->nextLevel()]();
    }
}

void Map::handleEvent(const sf::Event& event)
{
    auto& commands = mLevel->getCommandQueue();
    mLvlContext.context.player.handleEvent(event, commands);
    mLvlContext.playerInfo.backpack.handleEvent(event);
    mLvlContext.playerInfo.equipment.handleEvent(event);
}

void Map::draw()
{
    auto& context = mLvlContext.context;
    for (auto& component : *mGui)
			context.window.draw(*component.second);
    mLevel->draw();
    context.window.draw(mLvlContext.playerInfo.stats);
    context.window.draw(mLvlContext.playerInfo.backpack);
    context.window.draw(mLvlContext.playerInfo.equipment);
}

void Map::registerLevels()
{
    registerLevel<PrehistoryLevel>(LevelID::Prehistory);
    registerLevel<StartLevel>(LevelID::StartLevel);
    registerLevel<FirstLevel>(LevelID::FirstLevel);
}