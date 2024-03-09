/** @file StatisticsState.h */
#pragma once

#include "States/State.h"

class StatisticsState : public State {
public:
  StatisticsState(StateStack& stack,
                  Context& context);

private:
  void applyGuiFunctions();
};