/** @file GameState.h */
#pragma once

#include "Objects/Map.h"
#include "States/State.h"

class GameState : public State {
public:
  GameState(StateStack& stack, Context& context);
  virtual void draw() override;
  virtual bool update(sf::Time dt) override;
  virtual bool handleEvent(const sf::Event& event) override;

private:
  Map mMap;
};