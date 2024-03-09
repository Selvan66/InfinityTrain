/** @file LvlContext.h */
#pragma once

#include "App/Context.h"
#include "Player/PlayerInfo.h"

struct LvlContext {
  Context &context;
  PlayerInfo playerInfo;
  unsigned int numLevel;
};