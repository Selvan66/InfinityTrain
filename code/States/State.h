/** @file State.h */
#pragma once

#include "spdlog/spdlog.h"

#include "App/Context.h"
#include "States/StatesID.h"
#include "Utils/Exceptions/bad_function_call.h"
#include "Utils/Utility.h"

class StateStack;
class State {
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
  template <typename T> T& getGuiComponent(const std::string& id);

private:
  StateStack& mStack;
  Context& mContext;

  bool mIsGuiLoad;
  ParserGui::GuiParsePtr mGui;
};

template <typename T> T& State::getGuiComponent(const std::string& id) {
  if (!mIsGuiLoad) {
    spdlog::error("State::getGuiComponent | Gui not loaded in {}",
                  typeid(*this).name());
    throw Except::bad_function_call()
      .add(typeid(*this).name())
      .add("ERROR: use getGuiComponent "
           "before loadGuiParser");
  }
  return *(Utility::safeCasting<T>(mGui->at(id).get()));
}
