/** @file AboutState.h */
#pragma once

#include "States/State.h"

class AboutState : public State {
public:
  AboutState(StateStack& stack, Context& context);
  virtual bool update(sf::Time dt) override;
  virtual bool handleEvent(const sf::Event& event) override;

private:
  void applyGuiFunctions();
};
