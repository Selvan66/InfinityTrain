/** @file SettingState.cpp */
#include "States/SettingState.h"

#include <iostream> // to delete

SettingState::SettingState(StateStack& stack, Context& context)
: State(stack, context)
, mTextButtons()
{
    createButtons();
}

void SettingState::draw()
{
    auto& window = State::getContext().window;
    for (auto& button : mTextButtons)
		window.draw(button);
}

bool SettingState::update(sf::Time dt)
{
    for (auto& button : mTextButtons)
		button.update(dt);
	
    return true;
}

bool SettingState::handleEvent(const sf::Event& event)
{
    for (auto& button : mTextButtons)
		button.handleEvent(event);
	
    return true;
}

void SettingState::createButtons()
{
    auto& context = State::getContext();
	const sf::Vector2f& window_size = context.window.getView().getSize();
	const float buttonHeight = 65.f;
	mTextButtons.emplace_back(context);
	auto& playButton = mTextButtons.back();
	playButton.setText("GRAPHICS");
	playButton.setCallback([this]()
	{
		this->requestStackPop();
        this->requestStackPush(StatesID::GraphicsSettingState);
	});
	playButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2));
	
	mTextButtons.emplace_back(context);
	auto& achievementsButton = mTextButtons.back();
	achievementsButton.setText("CONTROL");
	achievementsButton.setCallback([](){std::cout << "CONTROL" << std::endl;});
	achievementsButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + buttonHeight));


	mTextButtons.emplace_back(context);
	auto& settingsButton = mTextButtons.back();
	settingsButton.setText("AUDIO");
	settingsButton.setCallback([this]()
	{
		this->requestStackPop();
        this->requestStackPush(StatesID::AudioSettingState);
	});
	settingsButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 2)));

	mTextButtons.emplace_back(context);
	auto& aboutButton = mTextButtons.back();
	aboutButton.setText("BACK");
	aboutButton.setCallback([this]()
    {
        this->requestStackPop();
        this->requestStackPush(StatesID::MenuOptionsState);
    });
	aboutButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 3)));
}
