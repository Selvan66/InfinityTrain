/** @file MenuOptionsState.h */
#pragma once

#include "States/State.h"

class MenuOptionsState : public State
{
    public:
		MenuOptionsState(StateStack& stack, Context& context);
	private:
		void applyGuiFunctions();
};