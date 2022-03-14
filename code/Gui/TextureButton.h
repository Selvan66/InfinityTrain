/** @file TextureButton.h */
#pragma once

#include "Gui/Button.h"

namespace GUI
{

class TextureButton : public Button
{
    public:
        TextureButton(Context& context, const sf::Texture& texture);
        void setRectNormal(const sf::IntRect& rect)
        void setRectSelected(const sf::IntRect& rect);
        void setRectPressed(const sf::IntRect& rect);
    private:
        virtual sf::FloatRect getGlobalBounds() const;
        virtual void changeTexture(Button::Type buttonType);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    private:
        const sf::Texture& mTexture;
        sf::Sprite mButtonSprite;
        sf::Sprite mSelectedButtonSprite;
        sf::Sprite mPressedButtonSprite;
};

}