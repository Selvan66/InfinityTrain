/** @file AudioSettingState.h */
#pragma once

#include "States/State.h"
#include "Gui/TextSlider.h"
#include "Gui/TextButton.h"

class AudioSettingState : public State
{
    public:
        AudioSettingState(StateStack& stack, Context& context);
        ~AudioSettingState();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
        void createGUI();
    private:
        sf::Text mMusic;
        float mSaveMusic;
        GUI::TextSlider mMusicSlider;

        sf::Text mSounds;
        float mSaveSound;
        GUI::TextSlider mSoundSlider;

        std::list<GUI::TextButton> mOptionButtons; 
};