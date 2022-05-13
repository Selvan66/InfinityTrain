/** @file GraphicsSettingState.h */
#pragma once

#include "States/State.h"
#include "Gui/TextSlider.h"
#include "Gui/Checkbox.h"
#include "Gui/TextButton.h"

class GraphicsSettingState : public State
{
    public:
        GraphicsSettingState(StateStack& stack, Context& context);
        virtual void draw() override;
        virtual bool update(sf::Time dt) override;
        virtual bool handleEvent(const sf::Event& event) override;
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