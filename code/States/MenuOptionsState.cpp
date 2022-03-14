/** @file MenuOptionsState.cpp */
#include "States/MenuOptionsState.h"
#include "Utils/Utility.h"

#include <iostream>	// to delete

MenuOptionsState::MenuOptionsState(StateStack& stack, Context& context)
: State(stack, context)
, mTextButtons()
{
    createButtons();
}

void MenuOptionsState::draw()
{
    auto& window = State::getContext().window;
    for (auto& button : mTextButtons)
	{
		window.draw(button);
	}
}

bool MenuOptionsState::update(sf::Time dt)
{
    for (auto& button : mTextButtons)
	{
		button.update(dt);
	}
	return true;
}

bool MenuOptionsState::handleEvent(const sf::Event& event)
{
    for (auto& button : mTextButtons)
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
	mTextButtons.emplace_back(context);
	auto& playButton = mTextButtons.back();
	playButton.setText("PLAY");
	playButton.setCallback([](){std::cout << "PLAY" << std::endl;});
	playButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2));
	
	mTextButtons.emplace_back(context);
	auto& achievementsButton = mTextButtons.back();
	achievementsButton.setText("ACHIEVEMENTS");
	achievementsButton.setCallback([](){std::cout << "ACHIEVEMENTS" << std::endl;});
	achievementsButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + buttonHeight));


	mTextButtons.emplace_back(context);
	auto& settingsButton = mTextButtons.back();
	settingsButton.setText("SETTINGS");
	settingsButton.setCallback([this]()
	{
		this->requestStackPop();
		this->requestStackPush(StatesID::SettingState);
	});
	settingsButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 2)));

	mTextButtons.emplace_back(context);
	auto& aboutButton = mTextButtons.back();
	aboutButton.setText("ABOUT");
	aboutButton.setCallback([](){std::cout << "ABOUT" << std::endl;});
	aboutButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 3)));

	mTextButtons.emplace_back(context);
	auto& quitButton = mTextButtons.back();
	quitButton.setText("QUIT");
	quitButton.setCallback([this](){this->requestStackClear();});
	quitButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 4)));
}
