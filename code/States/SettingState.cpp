/** @file SettingState.cpp */
#include "States/SettingState.h"
#include "Utils/Utility.h"
#include "Gui/TextButton.h"

SettingState::SettingState(StateStack& stack, Context& context)
: State(stack, context)
, mGui()
{
    createButtons();
}

void SettingState::draw()
{
    auto& window = State::getContext().window;
    for (auto& component : *mGui)
		window.draw(*component.second);
}

bool SettingState::update(sf::Time )
{
    for (auto& component : *mGui)
		component.second->update();
	
    return true;
}

bool SettingState::handleEvent(const sf::Event& event)
{
    for (auto& component : *mGui)
		component.second->handleEvent(event);
	
    return true;
}

void SettingState::createButtons()
{
    auto& context = State::getContext();
    const sf::Vector2f& window_size = context.window.getView().getSize();
    const float button_height = 65.f;
    
    ParserGui& parser = context.gui.get(GuiFileID::Setting);
    parser.addConst("BUTTON_HEIGHT", button_height);
    parser.addConst("WINDOW_WIDTH", window_size.x);
	parser.addConst("WINDOW_HEIGHT", window_size.y);
    mGui = parser.parse(context);
	
	Utility::safeCasting<TextButton>(mGui->at("GraphicsButton").get())->setCallback([this]()
	{
		this->requestStackPop();
        this->requestStackPush(StatesID::GraphicsSettingState);
	});
	
	Utility::safeCasting<TextButton>(mGui->at("ControlButton").get())->setCallback([this]()
	{
		this->requestStackPop();
        this->requestStackPush(StatesID::ControlSettingState);
	});

	Utility::safeCasting<TextButton>(mGui->at("AudioButton").get())->setCallback([this]()
	{
		this->requestStackPop();
        this->requestStackPush(StatesID::AudioSettingState);
	});

	Utility::safeCasting<TextButton>(mGui->at("BackButton").get())->setCallback([this]()
    {
        this->requestStackPop();
        this->requestStackPush(StatesID::MenuOptionsState);
    });
}
