/** @file MenuOptionsState.cpp */
#include "States/MenuOptionsState.h"
#include "Utils/Utility.h"

#include <iostream>	// to delete

MenuOptionsState::MenuOptionsState(StateStack& stack, Context& context)
: State(stack, context)
, mGui()
{
    createGUI();
}

void MenuOptionsState::draw()
{
    auto& window = State::getContext().window;
	for (auto& component : *mGui)
		window.draw(*component.second);
}

bool MenuOptionsState::update(sf::Time)
{
	for (auto& component : *mGui)
		component.second->update(); 
	return true;
}

bool MenuOptionsState::handleEvent(const sf::Event& event)
{
	for (auto& component : *mGui)
		component.second->handleEvent(event);
	return true;
}

void MenuOptionsState::createGUI()
{
	auto& context = State::getContext();
	const sf::Vector2f& window_size = context.window.getView().getSize();

	ParserGui& parser = context.gui.get(GuiFileID::MenuOptions);
	parser.addConst("WINDOW_WIDTH", window_size.x);
	parser.addConst("WINDOW_HEIGHT", window_size.y);
	parser.addConst("BUTTON_HEIGHT", 65.f);
	mGui = parser.parse(context);

	Utility::safeCasting<TextButton>(mGui->at("PlayButton").get())->setCallback([this]()
	{
		this->requestStackClear();
		this->requestStackPush(StatesID::LoadingState);
	});
	
	Utility::safeCasting<TextButton>(mGui->at("StatisticsButton").get())->setCallback([this]()
	{
		this->requestStackPop();
		this->requestStackPush(StatesID::StatisticsState);
	});

	Utility::safeCasting<TextButton>(mGui->at("SettingsButton").get())->setCallback([this]()
	{
		this->requestStackPop();
		this->requestStackPush(StatesID::SettingState);
	});

	Utility::safeCasting<TextButton>(mGui->at("AboutButton").get())->setCallback([]()
	{
		std::cout << "ABOUT" << std::endl;
	});

	Utility::safeCasting<TextButton>(mGui->at("QuitButton").get())->setCallback([this]()
	{
		this->requestStackClear();
	});
}
