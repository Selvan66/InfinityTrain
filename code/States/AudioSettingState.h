/** @file AudioSettingState.h */
#pragma once

#include "States/State.h"

class AudioSettingState : public State {
public:
  AudioSettingState(StateStack &stack, Context &context);

private:
  void applyGuiFunctions();

private:
  float mSaveMusic;
  float mSaveSound;
};