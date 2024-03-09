/** @file LoadingState.h */
#pragma once

#include "Effects/Animation.h"
#include "States/State.h"
#include "Utils/ParallelTask.h"

class LoadingState : public State {
public:
  LoadingState(StateStack &stack, Context &context);
  virtual void draw() override;
  virtual bool update(sf::Time dt) override;

private:
  void loadGameTextures();
  void loadGameGuiFiles();

private:
  ParallelTask mTexturesLoading;
  ParallelTask mGuiFilesLoading;
  Animation mLoading;
  static bool loaded;
};