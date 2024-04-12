/** @file AboutState.cpp */
#include "spdlog/spdlog.h"

#include "States/AboutState.h"

AboutState::AboutState(StateStack& stack, Context& context)
  : State(stack, context) {
  // State::loadGuiParser(GuiFileID::); // TOO
  applyGuiFunctions();

  spdlog::info("AboutState::AboutState | About State created");
}

void AboutState::applyGuiFunctions() {
  // TODO
}
