/** @file AudioSettingState.cpp */
#include "States/AudioSettingState.h"
#include "Gui/TextButton.h"
#include "Gui/TextSlider.h"

AudioSettingState::AudioSettingState(StateStack& stack, Context& context)
  : State(stack, context),
    mSaveMusic(context.settings.get<float>("Audio", "Music Volume")),
    mSaveSound(context.settings.get<float>("Audio", "Sounds Volume")) {
  State::loadGuiParser(GuiFileID::AudioSetting);
  applyGuiFunctions();
}

void AudioSettingState::applyGuiFunctions() {
  auto& context = State::getContext();

  State::getGuiComponent<TextSlider>("MusicSlider")
    .setCurrentText(std::to_string(static_cast<int>(mSaveMusic)));
  State::getGuiComponent<TextSlider>("SoundSlider")
    .setCurrentText(std::to_string(static_cast<int>(mSaveSound)));

  State::getGuiComponent<TextButton>("BackButton").setCallback([&]() {
    context.settings.set(mSaveMusic, "Audio", "Music Volume");
    context.settings.set(mSaveSound, "Audio", "Sounds Volume");
    context.applyAudioSettings();
    context.musics.replay();
    this->requestStackPop();
    this->requestStackPush(StatesID::SettingState);
  });

  State::getGuiComponent<TextButton>("ApplyButton").setCallback([&]() {
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