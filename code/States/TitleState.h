/** @file TitleState.h */
#pragma once

#include "States/State.h"

class TitleState : public State
{
	public:
		TitleState(StateStack& stack, Context& context);
		virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event& event);
	private:
		sf::Sprite mBackgroundSprite;
		sf::Text mTitle;
		sf::Text mStart;
		uint8_t mStartTransparency;
		bool mFadingStart;
		sf::Time mTextEffectTime;
};