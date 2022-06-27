/** @file GraphicsSettingState.h */
#pragma once

#include "States/State.h"
#include "Utils/ParserGui.h"

class GraphicsSettingState : public State
{
    public:
        GraphicsSettingState(StateStack& stack, Context& context);
        virtual void draw() override;
        virtual bool update(sf::Time dt) override;
        virtual bool handleEvent(const sf::Event& event) override;
    private:
        void createGUI();
    private:
        std::pair<int, int> mSaveResolution;
        bool mSaveFullscreen;

		ParserGui::GuiParsePtr mGui;
};