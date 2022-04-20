/** @file StateStack.cpp */
#include <cassert>

#include "States/StateStack.h"

StateStack::StateStack(Context& context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories()
{ }

void StateStack::update(sf::Time dt)
{
	for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
		if (!(*it)->update(dt))
			break;

	applyPendingChanges();
}

void StateStack::draw()
{
	for (auto& state : mStack)
		state->draw();
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
		if (!(*it)->handleEvent(event))
			break;
			
	applyPendingChanges();
}

void StateStack::pushState(StatesID stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearState()
{
	mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
	return mStack.empty();
}

State::Ptr StateStack::createState(StatesID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());
	return found->second();
}

void StateStack::applyPendingChanges()
{
	for (auto change : mPendingList)
	{
		switch (change.action)
		{
			case Push:
				mStack.push_back(createState(change.stateID));
				break;
			case Pop:
				mStack.pop_back();
				break;
			case Clear:
				mStack.clear();
				break;
		}
	}
	mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, StatesID stateID)
: action(action)
, stateID(stateID)
{ }
