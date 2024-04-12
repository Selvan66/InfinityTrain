/** @file AudioSettingState.cpp */
#include "spdlog/spdlog.h"

#include "Gui/TextButton.h"
#include "Gui/TextSlider.h"
#include "States/AudioSettingState.h"

AudioSettingState::AudioSettingState(StateStack& stack, Context& context)
  : State(stack, context),
    mSaveMusic(context.settings.get<float>("Audio", "Music Volume")),
    mSaveSound(context.settings.get<float>("Audio", "Sounds Volume")) {
  State::loadGuiParser(GuiFileID::AudioSetting);
  applyGuiFunctions();

  spdlog::info(
    "AudioSettingState::AudioSettingState | AudioSetting State created");
}

void AudioSettingState::applyGuiFunctions() {
  auto& context = State::getContext();

  State::getGuiComponent<TextSlider>("MusicSlider")
    .setCurrentText(std::to_string(static_cast<int>(mSaveMusic)));
  State::getGuiComponent<TextSlider>("SoundSlider")
    .setCurrentText(std::to_string(static_cast<int>(mSaveSound)));

  State::getGuiComponent<TextButton>("BackButton").setCallback([&]() {
    spdlog::trace("AudioSettingState::applyGuiFunctions | BackButton clicked");
    context.settings.set(mSaveMusic, "Audio", "Music Volume");
    context.settings.set(mSaveSound, "Audio", "Sounds Volume");
    context.applyAudioSettings();
    context.musics.replay();
    this->requestStackPop();
    this->requestStackPush(StatesID::SettingState);
  });

  State::getGuiComponent<TextButton>("ApplyButton").setCallback([&]() {
    spdlog::trace("AudioSettingState::applyGuiFunctions | ApplyButton clicked");
    float applyMusic = std::stof(
      State::getGuiComponent<TextSlider>("MusicSlider").getCurrentText());
    float applySound = std::stof(
      State::getGuiComponent<TextSlider>("SoundSlider").getCurrentText());
    context.settings.set(applyMusic, "Audio", "Music Volume");
    context.settings.set(applySound, "Audio", "Sounds Volume");
    context.applyAudioSettings();
    context.musics.replay();
  });

  State::getGuiComponent<TextButton>("ApplySaveButton").setCallback([&]() {
    spdlog::trace(
      "AudioSettingState::applyGuiFunctions | ApplySaveButton clicked");
    mSaveMusic = std::stof(
      State::getGuiComponent<TextSlider>("MusicSlider").getCurrentText());
    mSaveSound = std::stof(
      State::getGuiComponent<TextSlider>("SoundSlider").getCurrentText());
    context.settings.set(mSaveMusic, "Audio", "Music Volume");
    context.settings.set(mSaveSound, "Audio", "Sounds Volume");
    context.applyAudioSettings();
    context.musics.replay();
  });
}
