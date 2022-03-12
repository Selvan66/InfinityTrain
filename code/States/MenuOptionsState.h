/** @file MenuOptionsState.h */
#pragma once

#include "States/State.h"
#include "Gui/Button.h"

class MenuOptionsState : public State
{
    public:
		MenuOptionsState(StateStack& stack, Context& context);
		virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event& event);
	private:
		void createButtons();
	private:
		std::list<GUI::Button> mButtons;
};