/** @file StatisticsState.h */
#pragma once

#include "States/State.h"
#include "Gui/TextButton.h"

class StatisticsState : public State
{
    public:
        StatisticsState(StateStack& stack, Context& context);
        virtual void draw() override;
        virtual bool update(sf::Time dt) override;
        virtual bool handleEvent(const sf::Event& event) override;
    private:
        void createGUI();
    private:
        std::list<sf::Text> mTexts;
        TextButton mBackButton;
};