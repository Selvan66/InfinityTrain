/** @file GraphicsSettingState.h */
#pragma once

#include "States/State.h"
#include "Gui/TextSlider.h"
#include "Gui/Checkbox.h"
#include "Gui/TextButton.h"
#include "App/Settings.h"

class GraphicsSettingState : public State
{
    public:
        GraphicsSettingState(StateStack& stack, Context& context);
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
        void createGUI();
    private:
        sf::Text mResolution;
        std::pair<int, int> mSaveResolution;
        GUI::TextSlider mResolutionSlider;

        sf::Text mFullscreen;
        bool mSaveFullscreen;
        GUI::Checkbox mFullscreenCheckbox;

        std::list<GUI::TextButton> mOptionButtons; 
};