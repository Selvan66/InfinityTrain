/** @file SettingState.cpp */
#include "States/SettingState.h"

#include <iostream> // to delete

SettingState::SettingState(StateStack& stack, Context& context)
: State(stack, context)
, mButtons()
{
    createButtons();
}

void SettingState::draw()
{
    auto& window = State::getContext().window;
    for (auto& button : mButtons)
	{
		window.draw(button);
	}
}

bool SettingState::update(sf::Time dt)
{
    for (auto& button : mButtons)
	{
		button.update(dt);
	}
    return true;
}

bool SettingState::handleEvent(const sf::Event& event)
{
    for (auto& button : mButtons)
	{
		button.handleEvent(event);
	}
    return true;
}

void SettingState::createButtons()
{
    auto& context = State::getContext();
	const sf::Vector2f& window_size = context.window.getView().getSize();
	const float buttonHeight = 65.f;
	mButtons.emplace_back(context);
	auto& playButton = mButtons.back();
	playButton.setText("GRAPHICS");
	playButton.setCallback([](){std::cout << "GRAPHICS" << std::endl;});
	playButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2));
	
	mButtons.emplace_back(context);
	auto& achievementsButton = mButtons.back();
	achievementsButton.setText("CONTROL");
	achievementsButton.setCallback([](){std::cout << "CONTROL" << std::endl;});
	achievementsButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + buttonHeight));


	mButtons.emplace_back(context);
	auto& settingsButton = mButtons.back();
	settingsButton.setText("AUDIO");
	settingsButton.setCallback([this](){std::cout << "AUDIO" << std::endl;});
	settingsButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 2)));

	mButtons.emplace_back(context);
	auto& aboutButton = mButtons.back();
	aboutButton.setText("BACK");
	aboutButton.setCallback([this]()
    {
        this->requestStackPop();
        this->requestStackPush(StatesID::MenuState);
    });
	aboutButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 3)));
}
