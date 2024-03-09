/** @file StateStack.h */
#pragma once

#include <functional>

#include "States/State.h"

class StateStack : public sf::NonCopyable {
public:
  enum Action { Push, Pop, Clear };

public:
  explicit StateStack(Context &context);
  void update(sf::Time dt);
  void draw();
  void handleEvent(const sf::Event &event);
  void pushState(StatesID stateID);
  void popState();
  void clearState();
  bool isEmpty() const;

  template <typename T> void registerState(StatesID stateID);

private:
  State::Ptr createState(StatesID stateID);
  void applyPendingChanges();

private:
  struct PendingChange {
    PendingChange(Action action, StatesID stateID = StatesID::None);
    Action action;
    StatesID stateID;
  };

private:
  std::list<State::Ptr> mStack;
  std::list<PendingChange> mPendingList;
  Context &mContext;
  std::unordered_map<StatesID, std::function<State::Ptr()>> mFactories;
};

template <typename T> void StateStack::registerState(StatesID stateID) {
  mFactories[stateID] = [this] { return State::Ptr(new T(*this, mContext)); };
}