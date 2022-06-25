/** @file AudioSettingState.h */
#pragma once

#include "States/State.h"
#include "Utils/ParserGui.h"

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
        float mSaveMusic;
        float mSaveSound;

        ParserGui::GuiParsePtr mGui;
};