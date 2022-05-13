/** @file TextureButton.h */
#pragma once

#include "Gui/Button.h"

namespace GUI
{

class TextureButton : public Button
{
    public:
        TextureButton(Context& context, const sf::Texture& texture, sf::IntRect normal, sf::IntRect selected, sf::IntRect pressed);
    private:
        virtual sf::FloatRect getGlobalBounds() const override;
        virtual void changeTexture(Button::Type buttonType) override;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        const sf::Texture& mTexture;
        sf::IntRect mNormalRect;
        sf::IntRect mSelectedRect;
        sf::IntRect mPressedRect;
        sf::Sprite mButton;
};

}