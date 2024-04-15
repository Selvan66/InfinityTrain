/** @file MenuOptionsState.cpp */
#include "spdlog/spdlog.h"

#include "Gui/TextButton.h"
#include "States/MenuOptionsState.h"

MenuOptionsState::MenuOptionsState(StateStack& stack, Context& context)
  : State(stack, context) {
  State::loadGuiParser(GuiFileID::MenuOptions);
  applyGuiFunctions();
  spdlog::info(
    "MenuOptionsState::MenuOptionsState | MenuOptions State created");
}

void MenuOptionsState::applyGuiFunctions() {
  State::getGuiComponent<TextButton>("PlayButton").setCallback([this]() {
    spdlog::trace("MenuOptionsState::applyGuiFunctions | PlayButton clicked");
    this->requestStackClear();
    this->requestStackPush(StatesID::LoadingState);
  });

  State::getGuiComponent<TextButton>("StatisticsButton").setCallback([this]() {
    spdlog::trace(
      "MenuOptionsState::applyGuiFunctions | StatisticsButton clicked");
    this->requestStackPop();
    this->requestStackPush(StatesID::StatisticsState);
  });

  State::getGuiComponent<TextButton>("SettingsButton").setCallback([this]() {
    spdlog::trace(
      "MenuOptionsState::applyGuiFunctions | SettingsButton clicked");
    this->requestStackPop();
    this->requestStackPush(StatesID::SettingState);
  });

  State::getGuiComponent<TextButton>("AboutButton").setCallback([this]() {
    spdlog::trace("MenuOptionsState::applyGuiFunctions | AboutButton clicked");
    this->requestStackPop();
    this->requestStackPush(StatesID::AboutState);
  });

  State::getGuiComponent<TextButton>("QuitButton").setCallback([this]() {
    spdlog::trace("MenuOptionsState::applyGuiFunctions | QuitButton clicked");
    this->requestStackClear();
  });
}
