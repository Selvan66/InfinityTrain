/** @file GameOverState.h */
#pragma once

#include "States/State.h"

class GameOverState : public State {
public:
  GameOverState(StateStack& stack, Context& context);
  virtual void draw() override;
  virtual bool update(sf::Time dt) override;
  virtual bool handleEvent(const sf::Event& event) override;

private:
  sf::Time mElapsedTime;
  sf::RectangleShape mBackgroundShape;
};