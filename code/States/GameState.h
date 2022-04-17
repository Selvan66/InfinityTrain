/** @file GameState.h */
#pragma once

#include "States/State.h"
#include "Objects/Map.h"

class GameState : public State
{
    public:
        GameState(StateStack& stack, Context& context);
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
        Map mMap;
};