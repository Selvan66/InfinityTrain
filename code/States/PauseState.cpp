/** @file PauseState.cpp */
#include "States/PauseState.h"
#include "Gui/TextButton.h"

PauseState::PauseState(StateStack& stack, Context& context)
: State(stack, context)
, mBackgroundShape()
{
    mBackgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    mBackgroundShape.setSize(context.window.getView().getSize());

    State::loadGuiParser(GuiFileID::Pause);
    applyGuiFunctions();
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
    
	State::draw();
}

bool PauseState::update(sf::Time dt)
{
    State::update(dt);
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPop();
        
    State::handleEvent(event);

    return false;
}

void PauseState::applyGuiFunctions()
{
	State::getGuiComponent<TextButton>("BackButton").setCallback([this]()
	{
		this->requestStackPop();
	});
    
	State::getGuiComponent<TextButton>("QuitButton").setCallback([this]()
	{
		this->requestStackClear();
        this->requestStackPush(StatesID::MenuState);
	});
}