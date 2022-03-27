/** @file State.cpp */
#include "States/State.h"
#include "States/StateStack.h"

State::State(StateStack& stack, Context& context)
: mStack(stack)
, mContext(context)
{ }

State::~State()
{ }

void State::requestStackPush(StatesID stateID)
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