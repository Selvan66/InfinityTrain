/** @file MenuState.h */
#pragma once

#include "States/State.h"

class MenuState : public State
{
	public:
		MenuState(StateStack& stack, Context& context);
		virtual void draw() override;
		virtual bool update(sf::Time dt) override;
		virtual bool handleEvent(const sf::Event& event) override;
	private:
		sf::Sprite mBackgroundSprite;
		sf::Text mTitle;
};