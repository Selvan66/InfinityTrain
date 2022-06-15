/** @file AudioSettingState.h */
#pragma once

#include "States/State.h"
#include "Gui/TextSlider.h"
#include "Gui/TextButton.h"

class AudioSettingState : public State
{
    public:
        AudioSettingState(StateStack& stack, Context& context);
        virtual void draw() override;
        virtual bool update(sf::Time dt) override;
        virtual bool handleEvent(const sf::Event& event) override;
    private:
        void createGUI();
    private:
        sf::Text mMusic;
        float mSaveMusic;
        TextSlider mMusicSlider;

        sf::Text mSounds;
        float mSaveSound;
        TextSlider mSoundSlider;

        std::list<TextButton> mOptionButtons; 
};