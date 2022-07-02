/** @file State.h */
#pragma once

#include "States/StatesID.h"
#include "App/Context.h"
#include "Utils/ParserGui.h"
#include "Utils/Utility.h"

class StateStack;
class State
{
	public:
		typedef std::unique_ptr<State> Ptr;
	public:
		State(StateStack& stack, Context& context);
		virtual ~State();
		virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event& event);
	protected:
		void requestStackPush(StatesID stateID);
		void requestStackPop();
		void requestStackClear();
		Context& getContext() const;

		void loadGuiParser(GuiFileID guiFileID);
		template <typename T>
		T& getGuiComponent(const std::string& id);
	private:
		StateStack& mStack;
		Context& mContext;

		bool mIsGuiLoad;
		ParserGui::GuiParsePtr mGui;
};

template<typename T>
T& State::getGuiComponent(const std::string& id)
{
	if (!mIsGuiLoad)
		assert(true);		//TODO
	return *(Utility::safeCasting<T>(mGui->at(id).get()));
}