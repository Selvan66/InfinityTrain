/** @file PauseState.h */
#pragma once

#include "States/State.h"
#include "Utils/ParserGui.h"

class PauseState : public State
{
    public:
        PauseState(StateStack& stack, Context& context);
        ~PauseState();
        virtual void draw() override;
        virtual bool update(sf::Time dt) override;
        virtual bool handleEvent(const sf::Event& event) override;
    private:
        void createGUI();
    private:
        ParserGui::GuiParsePtr mGui;
        sf::RectangleShape mBackgroundShape;
};