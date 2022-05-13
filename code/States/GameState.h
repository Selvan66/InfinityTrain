/** @file GameState.h */
#pragma once

#include "States/State.h"
#include "Objects/Map.h"

class GameState : public State
{
    public:
        GameState(StateStack& stack, Context& context);
        virtual void draw() override;
        virtual bool update(sf::Time dt) override;
        virtual bool handleEvent(const sf::Event& event) override;
    private:
        Map mMap;
};