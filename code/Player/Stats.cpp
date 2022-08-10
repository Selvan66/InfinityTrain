/** @file Stats.cpp */
#include "Player/Stats.h"
#include "Utils/Utility.h"
#include "Gui/Text.h"

Stats::Stats(Context& context)
: mStats() 
{ 
    ParserGui& parser = context.gui.get(GuiFileID::Stats);
    parser.addConst("TEXT_HEIGHT", 40.f);
    mGui = parser.parse(context);

    setDefaultStats();
}

int Stats::getState(Type stat) const
{
    return mStats[stat];
}

bool Stats::setStat(Type stat, int value)
{
    auto oldStat = mStats[stat];
    setStatWithRange(stat, value);
    updateStatsText();
    return oldStat != mStats[stat];
}

bool Stats::updateStat(Type stat, int value)
{
    auto oldStat = mStats[stat];
    setStat(stat, mStats[stat] + value);
    updateStatsText();
    return oldStat != mStats[stat];
}

void Stats::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    states.transform = sf::Transformable::getTransform();
    for (auto& component : *mGui)
        target.draw(*component.second, states);
}

void Stats::updateStatsText()
{
    Utility::safeCasting<Text>(mGui->at("Lives").get())->setString("Lives: " + std::to_string(mStats[Lives]));
    Utility::safeCasting<Text>(mGui->at("Money").get())->setString("Money: " + std::to_string(mStats[Money]));
    Utility::safeCasting<Text>(mGui->at("Armor").get())->setString("Armor: " + std::to_string(mStats[Armor]));
    Utility::safeCasting<Text>(mGui->at("Attack").get())->setString("Attack: " + std::to_string(mStats[Attack]));
    Utility::safeCasting<Text>(mGui->at("Speed").get())->setString("Speed: " + std::to_string(mStats[Speed]));
}

void Stats::setDefaultStats()
{
    setStat(Lives, 100);
    setStat(Money, 0);
    setStat(Armor, 0);
    setStat(Attack, 0);
    setStat(Speed, 250);
}

void Stats::setStatWithRange(Type stat, int value)
{
    switch (stat)
    {
        case Lives:
        case Armor:
            mStats[stat] = std::min(100, std::max(value, 0));   // 0 <= stat <= 100
            break;
        case Money:
        case Attack:
            mStats[stat] = std::max(0, value);  // stat >= 0
            break;
        case Speed:
            mStats[stat] = std::max(25, value);  // stat >= 25
            break;
    }
}