#pragma once

#include <memory>

#include "States/StateStack.h"
#include "States/StatesID.h"
#include "App/Context.h"

class State
{
    public:
        typedef std::unique_ptr<State> Ptr;
    public:
        State(StateStack& stack, Context& context);
        virtual void draw() = 0;
        virtual void update(sf::Time dt) = 0;
        virtual void handleEvent(const sf::Event& event) = 0;
    protected:
        void requestStackPush(States::ID stateID);
        void requestStackPop();
        void requestStackClear();
        Context& getContext() const;
    private:
        StateStack& mStack;
        Context& mContext;
}