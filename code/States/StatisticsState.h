/** @file StatisticsState.h */
#pragma once

#include "States/State.h"
#include "Gui/TextButton.h"

class StatisticsState : public State
{
    public:
        StatisticsState(StateStack& stack, Context& context);
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
        void createGUI();
    private:
        std::list<sf::Text> mTexts;
        GUI::TextButton mBackButton;
};