/** @file PauseState.h */
#pragma once

#include "States/State.h"
#include "Gui/TextButton.h"

class PauseState : public State
{
    public:
        PauseState(StateStack& stack, Context& context);
        ~PauseState();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
        void createGUI();
    private:
        std::list<GUI::TextButton> mButtons;
        sf::RectangleShape mBackgroundShape;
};