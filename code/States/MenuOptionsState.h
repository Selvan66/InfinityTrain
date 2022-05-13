/** @file MenuOptionsState.h */
#pragma once

#include "States/State.h"
#include "Gui/TextButton.h"

class MenuOptionsState : public State
{
    public:
		MenuOptionsState(StateStack& stack, Context& context);
		virtual void draw() override;
		virtual bool update(sf::Time dt) override;
		virtual bool handleEvent(const sf::Event& event) override;
	private:
		void createButtons();
	private:
		std::list<GUI::TextButton> mTextButtons;
};