/** @file Checkbox.h */
#pragma once

#include "Gui/Button.h"

namespace GUI
{

class Checkbox : public Button
{
    public:
        Checkbox(Context& context);
        void setSelection(bool isSelect);
        bool isSelected() const;
    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        virtual sf::FloatRect getGlobalBounds() const;
    private:
        sf::Sprite mCheck;
        sf::RectangleShape mBox;
        bool mIsSelected;
};

}