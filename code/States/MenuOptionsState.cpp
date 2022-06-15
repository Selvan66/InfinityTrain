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
		window.draw(button);
}

bool MenuOptionsState::update(sf::Time)
{
    for (auto& button : mTextButtons)
		button.update();
	
	return true;
}

bool MenuOptionsState::handleEvent(const sf::Event& event)
{
    for (auto& button : mTextButtons)
		button.handleEvent(event);
	
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
	playButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2));
	playButton.setCallback([this]()
	{
		this->requestStackClear();
		this->requestStackPush(StatesID::LoadingState);
	});
	
	mTextButtons.emplace_back(context);
	auto& achievementsButton = mTextButtons.back();
	achievementsButton.setText("STATISTICS");
	achievementsButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + buttonHeight));
	achievementsButton.setCallback([this]()
	{
		this->requestStackPop();
		this->requestStackPush(StatesID::StatisticsState);
	});


	mTextButtons.emplace_back(context);
	auto& settingsButton = mTextButtons.back();
	settingsButton.setText("SETTINGS");
	settingsButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 2)));
	settingsButton.setCallback([this]()
	{
		this->requestStackPop();
		this->requestStackPush(StatesID::SettingState);
	});

	mTextButtons.emplace_back(context);
	auto& aboutButton = mTextButtons.back();
	aboutButton.setText("ABOUT");
	aboutButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 3)));
	aboutButton.setCallback([]()
	{
		std::cout << "ABOUT" << std::endl;
	});

	mTextButtons.emplace_back(context);
	auto& quitButton = mTextButtons.back();
	quitButton.setText("QUIT");
	quitButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 4)));
	quitButton.setCallback([this]()
	{
		this->requestStackClear();
	});
}
