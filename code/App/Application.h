#pragma once

#include "App/Context.h"
#include "States/StateStack.h" 

class Application
{
    public:
        Application();
        void run();
    private:
        void processInput();
        void update(sf::Time dt);
        void render();
        void registerStates();
    private:
        Context mContext;
        StateStack mStateStack;
};