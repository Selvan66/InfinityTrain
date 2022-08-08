/** @file PlayerInfo.h */
#pragma once

#include <SFML/Graphics.hpp>

#include "Player/Backpack.h"
#include "Player/Stats.h"
#include "Player/Equipment.h"

struct PlayerInfo
{
    explicit PlayerInfo(Context& context);

    Stats stats;
    Backpack backpack;
    Equipment equipment;
};