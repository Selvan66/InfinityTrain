/** @file State.h */
#pragma once

#include "States/StatesID.h"
#include "App/Context.h"

class StateStack;
class State
{
	public:
		typedef std::unique_ptr<State> Ptr;
	public:
		State(StateStack& stack, Context& context);
		virtual ~State();
		virtual void draw() = 0;
		virtual bool update(sf::Time dt) = 0;
		virtual bool handleEvent(const sf::Event& event) = 0;
	protected:
		void requestStackPush(StatesID stateID);
		void requestStackPop();
		void requestStackClear();
		Context& getContext() const;
	private:
		StateStack& mStack;
		Context& mContext;
};