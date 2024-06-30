/** @file AboutState.cpp */
#include "spdlog/spdlog.h"

#include "Gui/TextButton.h"
#include "States/AboutState.h"

AboutState::AboutState(StateStack& stack, Context& context)
  : State(stack, context) {
  State::loadGuiParser(GuiFileID::About);
  applyGuiFunctions();

  spdlog::info("AboutState::AboutState | About State created");
}

void AboutState::applyGuiFunctions() {
  State::getGuiComponent<TextButton>("BackButton").setCallback([this]() {
    spdlog::debug("AboutState::applyGuiFunctions | BackButton clicked");
    this->requestStackPop();
    this->requestStackPush(StatesID::MenuOptionsState);
  });
}
