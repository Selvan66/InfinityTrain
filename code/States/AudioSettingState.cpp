/** @file AudioSettingState.cpp */
#include "States/AudioSettingState.h"
#include "Utils/Utility.h"


AudioSettingState::AudioSettingState(StateStack& stack, Context& context)
: State(stack, context)
, mMusic("MUSIC VOLUME", context.fonts.get(FontsID::PixelFont), 60)
, mSaveMusic(context.settings.get<float>("Audio", "Music Volume"))
, mMusicSlider(context)
, mSounds("SOUND VOLUME", context.fonts.get(FontsID::PixelFont), 60)
, mSaveSound(context.settings.get<float>("Audio", "Sounds Volume"))
, mSoundSlider(context)
, mOptionButtons()
{
    for (int i = 0; i <= 100; i += 5)
    {
        mMusicSlider.addText(std::to_string(i));
    }
    mMusicSlider.setCurrentText(std::to_string((int)mSaveMusic));

    for (int i = 0; i <= 100; i += 5)
    {
        mSoundSlider.addText(std::to_string(i));
    }
    mSoundSlider.setCurrentText(std::to_string((int)mSaveSound));

    createGUI();
}

void AudioSettingState::draw()
{
    auto& window = State::getContext().window;
    window.draw(mMusic);
    window.draw(mMusicSlider);
    window.draw(mSounds);
    window.draw(mSoundSlider);
    for (auto& button : mOptionButtons)
	{
		window.draw(button);
	}
}

bool AudioSettingState::update(sf::Time dt)
{
    mMusicSlider.update(dt);
    mSoundSlider.update(dt);
    for (auto& button : mOptionButtons)
	{
		button.update(dt);
	}
    return true;
}

bool AudioSettingState::handleEvent(const sf::Event& event)
{
    mMusicSlider.handleEvent(event);
    mSoundSlider.handleEvent(event);
    for (auto& button : mOptionButtons)
	{
		button.handleEvent(event);
	}
    return true;
}

void AudioSettingState::createGUI()
{
    auto& context = State::getContext();
    const sf::Vector2f& windowsize = context.window.getView().getSize();

    Utility::centerOrigin(mMusic);
    mMusic.setOutlineThickness(2.f);
	mMusic.setOutlineColor(sf::Color(0, 0, 0));
    float textwidth = mMusic.getGlobalBounds().width * 3.f / 5.f;
    float textheight = mMusic.getGlobalBounds().height + 50.f;
    mMusic.setPosition(sf::Vector2f((windowsize.x / 2.f) - textwidth, windowsize.y / 2.f));
    mMusicSlider.setPosition((windowsize.x / 2.f) + textwidth, windowsize.y / 2.f);

    Utility::centerOrigin(mSounds);
    mSounds.setOutlineThickness(2.f);
	mSounds.setOutlineColor(sf::Color(0, 0, 0));
    mSounds.setPosition(sf::Vector2f((windowsize.x / 2.f) - textwidth, (windowsize.y / 2.f) + textheight));
    mSoundSlider.setPosition((windowsize.x / 2.f) + textwidth,(windowsize.y / 2.f) + textheight);


    mOptionButtons.emplace_back(context);
    auto& backButton = mOptionButtons.back();
    backButton.setText("BACK");
    backButton.setCallback([&]()
    {
        auto& context = State::getContext();
        context.settings.set(mSaveMusic, "Audio", "Music Volume");
        context.settings.set(mSaveSound, "Audio", "Sounds Volume");
        context.applyAudioSettings();
        context.musics.replay();
        this->requestStackPop();
        this->requestStackPush(StatesID::SettingState);
    });
    backButton.setPosition(sf::Vector2f(windowsize.x  * 2.f/8.f, windowsize.y * 4.f / 5.f));

    mOptionButtons.emplace_back(context);
    auto& applyButton = mOptionButtons.back();
    applyButton.setText("APPLY");
    applyButton.setCallback([&]()
    {
        float applyMusic = std::stof(mMusicSlider.getCurrentText());
        float applySound = std::stof(mSoundSlider.getCurrentText());
        context.settings.set(applyMusic, "Audio", "Music Volume");
        context.settings.set(applySound, "Audio", "Sounds Volume");
        context.applyAudioSettings();
        context.musics.replay();
    });
    applyButton.setPosition(sf::Vector2f(windowsize.x  * 4.f/8.f, windowsize.y * 4.f / 5.f));

    mOptionButtons.emplace_back(context);
    auto& saveButton = mOptionButtons.back();
    saveButton.setText("APPLY & SAVE");
    saveButton.setCallback([&]()
    {
        mSaveMusic = std::stof(mMusicSlider.getCurrentText());
        mSaveSound =std::stof(mSoundSlider.getCurrentText());
        context.settings.set(mSaveMusic, "Audio", "Music Volume");
        context.settings.set(mSaveSound, "Audio", "Sounds Volume");
        context.applyAudioSettings();
        context.musics.replay();
    });
    saveButton.setPosition(sf::Vector2f(windowsize.x  * 6.f/8.f, windowsize.y * 4.f / 5.f));
}
