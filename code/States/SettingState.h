/** @file SettingState.h */
#pragma once

#include "States/State.h"
#include "Utils/ParserGui.h"

class SettingState : public State
{
    public:
		SettingState(StateStack& stack, Context& context);
		virtual void draw() override;
		virtual bool update(sf::Time dt) override;
		virtual bool handleEvent(const sf::Event& event) override;
	private:
		void createButtons();
	private:
		ParserGui::GuiParsePtr mGui;
};