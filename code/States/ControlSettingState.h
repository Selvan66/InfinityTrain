/** @file ControlSettingState.h */
#pragma once
#include <array>
#include <unordered_map>

#include "States/State.h"
#include "Gui/TextButton.h"

class ControlSettingState : public State
{
    public:
        ControlSettingState(StateStack& stack, Context& context);
        virtual void draw() override;
        virtual bool update(sf::Time dt) override;
        virtual bool handleEvent(const sf::Event& event) override;
    private:
        void createGUI();
        void updateTextOnButton();
        void changeActionBinding(std::string key);
    private:
        std::array<GUI::TextButton, Player::ActionCount> mControlButton;
        std::unordered_map<std::string, std::string> mActionBinding;
        std::string mActionToChange;
        bool mChange;
        sf::RectangleShape mChangeBackground;
        sf::Text mChangeText;

        std::list<GUI::TextButton> mOptionButton;
};