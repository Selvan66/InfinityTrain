/** @file TextButton.h */
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
        virtual sf::FloatRect getGlobalBounds() const override;
        virtual void changeTexture(Button::Type buttonType) override;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        sf::Text mText;    
};

}