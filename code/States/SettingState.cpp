/** @file SettingState.cpp */
#include "States/SettingState.h"

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

bool SettingState::update(sf::Time )
{
    for (auto& button : mTextButtons)
		button.update();
	
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
	playButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2));
	playButton.setCallback([this]()
	{
		this->requestStackPop();
        this->requestStackPush(StatesID::GraphicsSettingState);
	});
	
	mTextButtons.emplace_back(context);
	auto& achievementsButton = mTextButtons.back();
	achievementsButton.setText("CONTROL");
	achievementsButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + buttonHeight));
	achievementsButton.setCallback([this]()
	{
		this->requestStackPop();
        this->requestStackPush(StatesID::ControlSettingState);
	});


	mTextButtons.emplace_back(context);
	auto& settingsButton = mTextButtons.back();
	settingsButton.setText("AUDIO");
	settingsButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 2)));
	settingsButton.setCallback([this]()
	{
		this->requestStackPop();
        this->requestStackPush(StatesID::AudioSettingState);
	});

	mTextButtons.emplace_back(context);
	auto& aboutButton = mTextButtons.back();
	aboutButton.setText("BACK");
	aboutButton.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2 + (buttonHeight * 3)));
	aboutButton.setCallback([this]()
    {
        this->requestStackPop();
        this->requestStackPush(StatesID::MenuOptionsState);
    });
}
