/** @file PauseState.cpp */
#include "States/PauseState.h"
#include "Utils/Utility.h"

PauseState::PauseState(StateStack& stack, Context& context)
: State(stack, context)
, mButtons()
{
    createGUI();
}

void PauseState::draw()
{
    auto& window = State::getContext().window;
    for (auto& button : mButtons)
	{
		window.draw(button);
	}
}

bool PauseState::update(sf::Time dt)
{
    for (auto& button : mButtons)
    {
        button.update(dt);
    }
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    for (auto& button : mButtons)
    {
        button.handleEvent(event);
    }
    return false;
}

void PauseState::createGUI()
{
    auto& context = State::getContext();
    const sf::Vector2f& windowSize = context.window.getView().getSize();
    const float buttonHeight = 65.f;
    
    mButtons.emplace_back(context);
	auto& backButton = mButtons.back();
	backButton.setText("BACK");
	backButton.setCallback([this]()
	{
		this->requestStackPop();
	});
	backButton.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2));

    mButtons.emplace_back(context);
	auto& quitButton = mButtons.back();
	quitButton.setText("QUIT");
	quitButton.setCallback([this]()
	{
		this->requestStackClear();
        this->requestStackPush(StatesID::MenuState);
	});
	quitButton.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + buttonHeight));
}