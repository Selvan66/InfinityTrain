/** @file Stats.cpp */
#include "Player/Stats.h"

Stats::Stats()
: mStats() 
{ }

int Stats::getState(Type stat) const
{
    return mStats[stat];
}

void Stats::setStat(Type stat, int value)
{
    mStats[stat] = value;
}

void Stats::updateStat(Type stat, int value)
{
    mStats[stat] += value;
}

void Stats::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    //...
}
