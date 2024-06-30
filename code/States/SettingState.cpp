/** @file SettingState.cpp */
#include "spdlog/spdlog.h"

#include "Gui/TextButton.h"
#include "States/SettingState.h"

SettingState::SettingState(StateStack& stack, Context& context)
  : State(stack, context) {
  State::loadGuiParser(GuiFileID::Setting);
  applyGuiFunctions();
  spdlog::info("SettingState::SettingState | Setting State created");
}

void SettingState::applyGuiFunctions() {
  State::getGuiComponent<TextButton>("GraphicsButton").setCallback([this]() {
    spdlog::debug("SettingState::applyGuiFunctions | GraphicsButton clicked");
    this->requestStackPop();
    this->requestStackPush(StatesID::GraphicsSettingState);
  });

  State::getGuiComponent<TextButton>("ControlButton").setCallback([this]() {
    spdlog::debug("SettingState::applyGuiFunctions | ControlButton clicked");
    this->requestStackPop();
    this->requestStackPush(StatesID::ControlSettingState);
  });

  State::getGuiComponent<TextButton>("AudioButton").setCallback([this]() {
    spdlog::debug("SettingState::applyGuiFunctions | AudioButton clicked");
    this->requestStackPop();
    this->requestStackPush(StatesID::AudioSettingState);
  });

  State::getGuiComponent<TextButton>("BackButton").setCallback([this]() {
    spdlog::debug("SettingState::applyGuiFunctions | BackButton clicked");
    this->requestStackPop();
    this->requestStackPush(StatesID::MenuOptionsState);
  });
}
