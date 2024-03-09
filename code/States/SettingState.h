/** @file SettingState.h */
#pragma once

#include "States/State.h"

class SettingState : public State {
public:
  SettingState(StateStack& stack, Context& context);

private:
  void applyGuiFunctions();
};