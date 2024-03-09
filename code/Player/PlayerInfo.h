/** @file PlayerInfo.h */
#pragma once

#include <SFML/Graphics.hpp>

#include "Player/Backpack.h"
#include "Player/Equipment.h"
#include "Player/Stats.h"

struct PlayerInfo {
  explicit PlayerInfo(Context &context);

  Stats stats;
  Backpack backpack;
  Equipment equipment;
};