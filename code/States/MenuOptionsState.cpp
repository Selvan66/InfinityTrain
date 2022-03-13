/** @file MenuOptionsState.cpp */
#include "States/MenuOptionsState.h"
#include "Utils/Utility.h"

#include <iostream>	// to delete

MenuOptionsState::MenuOptionsState(StateStack& stack, Context& context)
: State(stack, context)
, mButtons()
{
    createButtons();
}

void MenuOptionsState::draw()
{
    auto& window = State::getContext().window;
    for (auto& button : mButtons)
	{
		window.draw(button);
	}
}

bool MenuOptionsState::update(sf::Time dt)
{
    for (auto& button : mButtons)
	{
		button.update(dt);
	}
	return true;
}

bool MenuOptionsState::handleEvent(const sf::Event& event)
{
    for (auto& button : mButtons)
	{
		button.handleEvent(event);
	}
	return true;
}

void MenuOptionsState::createButtons()
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
	settingsButton.setCallback([this]()
	{
		this->requestStackPop();
		this->requestStackPush(StatesID::SettingState);
	});
	settingsButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 2)));

	mButtons.emplace_back(context);
	auto& aboutButton = mButtons.back();
	aboutButton.setText("ABOUT");
	aboutButton.setCallback([](){std::cout << "ABOUT" << std::endl;});
	aboutButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 3)));

	mButtons.emplace_back(context);
	auto& quitButton = mButtons.back();
	quitButton.setText("QUIT");
	quitButton.setCallback([this](){this->requestStackClear();});
	quitButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 4)));
}
