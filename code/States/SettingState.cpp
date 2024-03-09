/** @file SettingState.cpp */
#include "States/SettingState.h"
#include "Gui/TextButton.h"

SettingState::SettingState(StateStack &stack, Context &context)
    : State(stack, context) {
  State::loadGuiParser(GuiFileID::Setting);
  applyGuiFunctions();
}

void SettingState::applyGuiFunctions() {
  State::getGuiComponent<TextButton>("GraphicsButton").setCallback([this]() {
    this->requestStackPop();
    this->requestStackPush(StatesID::GraphicsSettingState);
  });

  State::getGuiComponent<TextButton>("ControlButton").setCallback([this]() {
    this->requestStackPop();
    this->requestStackPush(StatesID::ControlSettingState);
  });

  State::getGuiComponent<TextButton>("AudioButton").setCallback([this]() {
    this->requestStackPop();
    this->requestStackPush(StatesID::AudioSettingState);
  });

  State::getGuiComponent<TextButton>("BackButton").setCallback([this]() {
    this->requestStackPop();
    this->requestStackPush(StatesID::MenuOptionsState);
  });
}