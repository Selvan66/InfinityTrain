/** @file Button.h */
#pragma once

#include "Gui/Button.h"

namespace GUI
{

class TextButton : public Button
{
    public:
        TextButton(Context& context);
        void setText(const std::string& text);
    private:
        virtual sf::FloatRect getGlobalBounds() const;
        virtual void changeTexture(Button::Type buttonType);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    private:
        sf::Text mText;    
};

}