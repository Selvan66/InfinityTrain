/** @file GraphicsSettingState.h */
#pragma once

#include "States/State.h"

class GraphicsSettingState : public State {
public:
  GraphicsSettingState(StateStack &stack, Context &context);
  virtual bool update(sf::Time dt) override;

private:
  void applyGuiFunctions();

private:
  std::pair<int, int> mSaveResolution;
  bool mSaveFullscreen;
};