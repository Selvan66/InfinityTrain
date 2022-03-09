/** @file MenuState.h */
#pragma once

#include "States/State.h"
#include "Gui/PopupLabel.h"
#include "Gui/Button.h"

class MenuState : public State
{
	public:
		MenuState(StateStack& stack, Context& context);
		virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event& event);
	private:
		void createButtons();
	private:
		sf::Sprite mBackgroundSprite;
		sf::Text mTitle;

		std::list<GUI::Button> mButtons;
};