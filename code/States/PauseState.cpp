/** @file PauseState.cpp */
#include "States/PauseState.h"
#include "Utils/Utility.h"
#include "Gui/TextButton.h"

PauseState::PauseState(StateStack& stack, Context& context)
: State(stack, context)
, mGui()
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
    for (auto& component : *mGui)
		window.draw(*component.second);
	
}

bool PauseState::update(sf::Time)
{
    for (auto& component : *mGui)
		component.second->update();
    
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPop();
        
    for (auto& component : *mGui)
		component.second->handleEvent(event);

    return false;
}

void PauseState::createGUI()
{
    auto& context = State::getContext();
    const sf::Vector2f& window_size = context.window.getView().getSize();
    const float button_height = 65.f;
    
    mBackgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    mBackgroundShape.setSize(context.window.getView().getSize());

    ParserGui& parser = context.gui.get(GuiFileID::Pause);
    parser.addConst("BUTTON_HEIGHT", button_height);
    parser.addConst("WINDOW_WIDTH", window_size.x);
	parser.addConst("WINDOW_HEIGHT", window_size.y);
    mGui = parser.parse(context);

	Utility::safeCasting<TextButton>(mGui->at("BackButton").get())->setCallback([this]()
	{
		this->requestStackPop();
	});

	Utility::safeCasting<TextButton>(mGui->at("QuitButton").get())->setCallback([this]()
	{
		this->requestStackClear();
        this->requestStackPush(StatesID::MenuState);
	});
}
