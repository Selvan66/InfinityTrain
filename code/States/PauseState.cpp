/** @file PauseState.cpp */
#include "States/PauseState.h"
#include "Utils/Utility.h"

PauseState::PauseState(StateStack& stack, Context& context)
: State(stack, context)
, mButtons()
, mBackgroundShape()
{
    createGUI();
    context.musics.setPaused(true);
}

PauseState::~PauseState()
{
    State::getContext().musics.setPaused(false);
}

void PauseState::draw()
{
    auto& window = State::getContext().window;
    window.draw(mBackgroundShape);
    for (auto& button : mButtons)
		window.draw(button);
	
}

bool PauseState::update(sf::Time)
{
    for (auto& button : mButtons)
        button.update();
    
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPop();
        
    for (auto& button : mButtons)
        button.handleEvent(event);

    return false;
}

void PauseState::createGUI()
{
    auto& context = State::getContext();
    const sf::Vector2f& windowSize = context.window.getView().getSize();
    const float buttonHeight = 65.f;
    
    mBackgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    mBackgroundShape.setSize(context.window.getView().getSize());

    mButtons.emplace_back(context);
	auto& backButton = mButtons.back();
	backButton.setText("BACK");
	backButton.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2));
	backButton.setCallback([this]()
	{
		this->requestStackPop();
	});

    mButtons.emplace_back(context);
	auto& quitButton = mButtons.back();
	quitButton.setText("QUIT");
	quitButton.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + buttonHeight));
	quitButton.setCallback([this]()
	{
		this->requestStackClear();
        this->requestStackPush(StatesID::MenuState);
	});
}
