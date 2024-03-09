/** @file MenuState.h */
#pragma once

#include "States/State.h"

class MenuState : public State {
public:
  MenuState(StateStack& stack,
            Context& context);
  virtual void draw() override;

private:
  sf::Sprite mBackgroundSprite;
  sf::Text mTitle;
};