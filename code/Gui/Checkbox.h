/** @file Checkbox.h */
#pragma once

#include "Gui/Button.h"
class Checkbox : public Button
{
    public:
        Checkbox(Context& context);
        void setSelection(bool isSelect);
        bool isSelected() const;
    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual sf::FloatRect getGlobalBounds() const override;
    private:
        sf::Sprite mCheck;
        sf::RectangleShape mBox;
        bool mIsSelected;
};