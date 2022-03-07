/** @file TitleState.cpp */
#include "States/TitleState.h"
#include "Utils/Utility.h"

TitleState::TitleState(StateStack& stack, Context& context)
: State(stack, context)
, mBackgroundSprite()
, mTitle()
, mStart()
, mStartTransparency(255)
, mFadingStart(true)
, mTextEffectTime(sf::Time::Zero)
, mLabel("TESTTESTEASTTTTTTTTTTTTTTTT\nTEEEEEEEEEEEEEEEEEETTTTTTTTTT\nTEST", context.fonts)
{
	const sf::Vector2f& window_size = context.window.getView().getSize();

	mBackgroundSprite.setTexture(context.textures.get(TexturesID::TitleScreen));
	
	mTitle.setFont(context.fonts.get(FontsID::PixelFont));
	mTitle.setString("INFINITY TRAIN");
	mTitle.setCharacterSize(64);
	mTitle.setOutlineThickness(1);
	mTitle.setOutlineColor(sf::Color(0, 0, 0));
	Utility::centerOrigin(mTitle);
	mTitle.setPosition(sf::Vector2f(window_size.x / 2.f, window_size.y / 5.f));

	mStart.setFont(context.fonts.get(FontsID::PixelFont));
	mStart.setString("PRESS ANY KEY TO START");
	mStart.setCharacterSize(38);
	Utility::centerOrigin(mStart);
	mStart.setPosition(sf::Vector2f(window_size.x / 2.f, window_size.y * 3.f / 4.f));
}

void TitleState::draw()
{
	auto& window = State::getContext().window;
	window.draw(mBackgroundSprite);
	window.draw(mTitle);
	window.draw(mLabel);
	auto& color = mStart.getFillColor();
	mStart.setFillColor(sf::Color(color.r, color.g, color.g, mStartTransparency));
	window.draw(mStart);
}

bool TitleState::update(sf::Time dt)
{
	mTextEffectTime += dt;
	if (mTextEffectTime >= sf::milliseconds(10)) {
		mTextEffectTime = sf::Time::Zero;
		if (mFadingStart)
		{
			mStartTransparency -= 5;
			if (mStartTransparency <= 5)
			{
				mFadingStart = false;
			}
		}
		else
		{
			mStartTransparency += 5;
			if (mStartTransparency >= 250)
			{
				mFadingStart = true;
			}
		}
	}

	sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(State::getContext().window));
	mLabel.checkPopup(mTitle.getGlobalBounds(), mouse_pos);

	return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop();
		//requestStackPush(States::Menu);
	}
	return true;
}
