/** @file GraphicsSettingState.cpp */
#include "States/GraphicsSettingState.h"
#include "Gui/Checkbox.h"
#include "Gui/TextButton.h"
#include "Gui/TextSlider.h"

GraphicsSettingState::GraphicsSettingState(StateStack& stack, Context& context)
  : State(stack, context),
    mSaveResolution(
      context.settings.get<std::pair<int, int>>("Graphics", "Resolution")),
    mSaveFullscreen(context.settings.get<bool>("Graphics", "Fullscreen")) {
  State::loadGuiParser(GuiFileID::GraphicsSetting);
  applyGuiFunctions();
}

bool GraphicsSettingState::update(sf::Time dt) {
  State::update(dt);

  if (State::getGuiComponent<Checkbox>("FullscreenBox").isSelected())
    State::getGuiComponent<TextSlider>("ResolutionSlider")
      .setCurrentText("1920x1080");

  return true;
}

void GraphicsSettingState::applyGuiFunctions() {
  auto& context = State::getContext();

  std::string currentResolution = std::to_string(mSaveResolution.first) + "x" +
                                  std::to_string(mSaveResolution.second);
  State::getGuiComponent<TextSlider>("ResolutionSlider")
    .setCurrentText(currentResolution);
  State::getGuiComponent<Checkbox>("FullscreenBox")
    .setSelection(mSaveFullscreen);

  State::getGuiComponent<TextButton>("BackButton").setCallback([&]() {
    context.settings.set<std::pair<int, int>>(mSaveResolution, "Graphics",
                                              "Resolution");
    context.settings.set<bool>(mSaveFullscreen, "Graphics", "Fullscreen");
    context.applyGraphicSettings();
    this->requestStackPop();
    this->requestStackPush(StatesID::SettingState);
  });

  State::getGuiComponent<TextButton>("ApplyButton").setCallback([&]() {
    std::string applyResolution =
      State::getGuiComponent<TextSlider>("ResolutionSlider").getCurrentText();
    std::string width = applyResolution.substr(0, applyResolution.find('x'));
    std::string height = applyResolution.substr(applyResolution.find('x') + 1,
                                                applyResolution.size());
    context.settings.set<std::pair<int, int>>(
      std::pair<int, int>(std::stoi(width), std::stoi(height)), "Graphics",
      "Resolution");
    context.settings.set<bool>(
      State::getGuiComponent<Checkbox>("FullscreenBox").isSelected(),
      "Graphics", "Fullscreen");
    context.applyGraphicSettings();
  });

  State::getGuiComponent<TextButton>("ApplySaveButton").setCallback([&]() {
    std::string applyResolution =
      State::getGuiComponent<TextSlider>("ResolutionSlider").getCurrentText();
    std::string width = applyResolution.substr(0, applyResolution.find('x'));
    std::string height = applyResolution.substr(applyResolution.find('x') + 1,
                                                applyResolution.size());
    mSaveResolution = std::pair<int, int>(std::stoi(width), std::stoi(height));
    mSaveFullscreen =
      State::getGuiComponent<Checkbox>("FullscreenBox").isSelected();
    context.settings.set<std::pair<int, int>>(mSaveResolution, "Graphics",
                                              "Resolution");
    context.settings.set<bool>(mSaveFullscreen, "Graphics", "Fullscreen");
    context.applyGraphicSettings();
  });
}