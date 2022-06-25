/** @file AudioSettingState.cpp */
#include "States/AudioSettingState.h"
#include "Utils/Utility.h"
#include "Gui/TextSlider.h"
#include "Gui/TextButton.h"

AudioSettingState::AudioSettingState(StateStack& stack, Context& context)
: State(stack, context)
, mSaveMusic(context.settings.get<float>("Audio", "Music Volume"))
, mSaveSound(context.settings.get<float>("Audio", "Sounds Volume"))
, mGui()
{
    createGUI();
}

void AudioSettingState::draw()
{
    auto& window = State::getContext().window;
    for (auto& component : *mGui)
		window.draw(*component.second);
}

bool AudioSettingState::update(sf::Time)
{
    for (auto& component : *mGui)
		component.second->update(); 
    return true;
}

bool AudioSettingState::handleEvent(const sf::Event& event)
{
    for (auto& component : *mGui)
		component.second->handleEvent(event);
    return true;
}

void AudioSettingState::createGUI()
{
    auto& context = State::getContext();
    const sf::Vector2f& window_size = context.window.getView().getSize();

    ParserGui& parser = context.gui.get(GuiFileID::AudioSetting);
    parser.addConst("TEXT_HEIGHT", 100.f);
    parser.addConst("TEXT_WIDTH", 270.f);
    parser.addConst("WINDOW_WIDTH", window_size.x);
	parser.addConst("WINDOW_HEIGHT", window_size.y);
    mGui = parser.parse(context);

    Utility::safeCasting<TextSlider>(mGui->at("MusicSlider").get())->setCurrentText(std::to_string(static_cast<int>(mSaveMusic)));
    Utility::safeCasting<TextSlider>(mGui->at("SoundSlider").get())->setCurrentText(std::to_string(static_cast<int>(mSaveSound)));
    
    Utility::safeCasting<TextButton>(mGui->at("BackButton").get())->setCallback([&]()
    {
        auto& context = State::getContext();
        context.settings.set(mSaveMusic, "Audio", "Music Volume");
        context.settings.set(mSaveSound, "Audio", "Sounds Volume");
        context.applyAudioSettings();
        context.musics.replay();
        this->requestStackPop();
        this->requestStackPush(StatesID::SettingState);
    });

    Utility::safeCasting<TextButton>(mGui->at("ApplyButton").get())->setCallback([&]()
    {
        float applyMusic = std::stof(Utility::safeCasting<TextSlider>(mGui->at("MusicSlider").get())->getCurrentText());
        float applySound = std::stof(Utility::safeCasting<TextSlider>(mGui->at("SoundSlider").get())->getCurrentText());
        context.settings.set(applyMusic, "Audio", "Music Volume");
        context.settings.set(applySound, "Audio", "Sounds Volume");
        context.applyAudioSettings();
        context.musics.replay();
    });

    Utility::safeCasting<TextButton>(mGui->at("ApplySaveButton").get())->setCallback([&]()
    {
        mSaveMusic = std::stof(Utility::safeCasting<TextSlider>(mGui->at("MusicSlider").get())->getCurrentText());
        mSaveSound =std::stof(Utility::safeCasting<TextSlider>(mGui->at("SoundSlider").get())->getCurrentText());
        context.settings.set(mSaveMusic, "Audio", "Music Volume");
        context.settings.set(mSaveSound, "Audio", "Sounds Volume");
        context.applyAudioSettings();
        context.musics.replay();
    });
}
