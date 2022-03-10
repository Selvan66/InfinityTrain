/** @file MenuState.cpp */
#include "States/MenuState.h"
#include "Utils/Utility.h"

#include <iostream>

MenuState::MenuState(StateStack& stack, Context& context)
: State(stack, context)
, mBackgroundSprite()
, mTitle()
, mButtons()
{
	const sf::Vector2f& window_size = context.window.getView().getSize();

	mBackgroundSprite.setTexture(context.textures.get(TexturesID::TitleScreen));
	
	mTitle.setFont(context.fonts.get(FontsID::PixelFont));
	mTitle.setString("INFINITY TRAIN");
	mTitle.setCharacterSize(120);
	mTitle.setOutlineThickness(2.f);
	mTitle.setOutlineColor(sf::Color(0, 0, 0));
	Utility::centerOrigin(mTitle);
	mTitle.setPosition(sf::Vector2f(window_size.x / 2.f, window_size.y / 5.f));

	createButtons();
}

void MenuState::draw()
{
	auto& window = State::getContext().window;
	window.draw(mBackgroundSprite);
	window.draw(mTitle);
	for (auto& button : mButtons)
	{
		window.draw(button);
	}
}

bool MenuState::update(sf::Time dt)
{
	for (auto& button : mButtons)
	{
		button.update(dt);
	}
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	for (auto& button : mButtons)
	{
		button.handleEvent(event);
	}
	return true;
}

void MenuState::createButtons()
{
	auto& context = State::getContext();
	const sf::Vector2f& window_size = context.window.getView().getSize();
	const float buttonHeight = 65.f;
	mButtons.emplace_back(context);
	auto& playButton = mButtons.back();
	playButton.setText("PLAY");
	playButton.setCallback([](){std::cout << "PLAY" << std::endl;});
	playButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2));
	
	mButtons.emplace_back(context);
	auto& achievementsButton = mButtons.back();
	achievementsButton.setText("ACHIEVEMENTS");
	achievementsButton.setCallback([](){std::cout << "ACHIEVEMENTS" << std::endl;});
	achievementsButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + buttonHeight));


	mButtons.emplace_back(context);
	auto& settingsButton = mButtons.back();
	settingsButton.setText("SETTINGS");
	settingsButton.setCallback([](){std::cout << "SETTINGS" << std::endl;});
	settingsButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 2)));

	mButtons.emplace_back(context);
	auto& aboutButton = mButtons.back();
	aboutButton.setText("ABOUT");
	aboutButton.setCallback([](){std::cout << "ABOUT" << std::endl;});
	aboutButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 3)));

	mButtons.emplace_back(context);
	auto& quitButton = mButtons.back();
	quitButton.setText("QUIT");
	quitButton.setCallback([this](){this->requestStackPop();});
	quitButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 4)));
}
