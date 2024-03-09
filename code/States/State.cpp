/** @file State.cpp */
#include "States/State.h"
#include "States/StateStack.h"

State::State(StateStack& stack, Context& context)
  : mStack(stack), mContext(context), mIsGuiLoad(false), mGui() {}

State::~State() {}

void State::draw() {
  if (mIsGuiLoad) {
    auto& window = mContext.window;
    for (auto& component : *mGui)
      window.draw(*component.second);
  }
}

bool State::update(sf::Time dt) {
  if (mIsGuiLoad)
    for (auto& component : *mGui)
      component.second->update();
  return true;
}

bool State::handleEvent(const sf::Event& event) {
  if (mIsGuiLoad)
    for (auto& component : *mGui)
      component.second->handleEvent(event);
  return true;
}

void State::requestStackPush(StatesID stateID) { mStack.pushState(stateID); }

void State::requestStackPop() { mStack.popState(); }

void State::requestStackClear() { mStack.clearState(); }

Context& State::getContext() const { return mContext; }

void State::loadGuiParser(GuiFileID guiFileID) {
  const sf::Vector2f& window_size = mContext.window.getView().getSize();

  ParserGui& parser = mContext.gui.get(guiFileID);
  parser.addConst("WINDOW_WIDTH", window_size.x);
  parser.addConst("WINDOW_HEIGHT", window_size.y);
  parser.addConst("TEXT_HEIGHT", 100.f);
  parser.addConst("TEXT_WIDTH", 270.f);
  parser.addConst("BUTTON_HEIGHT", 65.f);
  mGui = parser.parse(mContext);

  mIsGuiLoad = true;
}