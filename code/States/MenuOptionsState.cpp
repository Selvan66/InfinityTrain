/** @file MenuOptionsState.cpp */
#include "States/MenuOptionsState.h"
#include "Gui/TextButton.h"

#include <iostream>	// to delete

MenuOptionsState::MenuOptionsState(StateStack& stack, Context& context)
: State(stack, context)
{
	State::loadGuiParser(GuiFileID::MenuOptions);
    applyGuiFunctions();
}

void MenuOptionsState::applyGuiFunctions()
{
	State::getGuiComponent<TextButton>("PlayButton").setCallback([this]()
	{
		this->requestStackClear();
		this->requestStackPush(StatesID::LoadingState);
	});
	
	State::getGuiComponent<TextButton>("StatisticsButton").setCallback([this]()
	{
		this->requestStackPop();
		this->requestStackPush(StatesID::StatisticsState);
	});

	State::getGuiComponent<TextButton>("SettingsButton").setCallback([this]()
	{
		this->requestStackPop();
		this->requestStackPush(StatesID::SettingState);
	});

	State::getGuiComponent<TextButton>("AboutButton").setCallback([]()
	{
		std::cout << "ABOUT" << std::endl;	//< To change
	});

	State::getGuiComponent<TextButton>("QuitButton").setCallback([this]()
	{
		this->requestStackClear();
	});
}