/** @file AboutState.h */
#pragma once

#include "States/State.h"

class AboutState : public State {
public:
  AboutState(StateStack& stack, Context& context);

private:
  void applyGuiFunctions();
};
