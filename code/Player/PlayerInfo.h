/** @file PlayerInfo.h */
#pragma once

#include <SFML/Graphics.hpp>

#include "Player/Backpack.h"
#include "Player/Stats.h"

struct PlayerInfo
{
    Stats stats;
    Backpack backpack;
};