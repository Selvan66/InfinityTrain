/** @file PlayerInfo.h */
#pragma once

#include "Player/Backpack.h"

struct PlayerInfo
{
    unsigned int lives;
    unsigned int money;
    Backpack backpack;
};