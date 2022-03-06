/** @file State.cpp */
#include "States/State.h"
#include "States/StateStack.h"

State::State(StateStack& stack, Context& context)
: mStack(stack)
, mContext(context)
{   
}

void State::requestStackPush(States::ID stateID)
{
    mStack.pushState(stateID);
}

void State::requestStackPop()
{
    mStack.popState();
}

void State::requestStackClear()
{
    mStack.clearState();
}

Context& State::getContext() const
{
    return mContext;
}