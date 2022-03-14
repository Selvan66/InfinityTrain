/** @file TextureButton.cpp */
#include "Gui/TextureButton.h"
#include "Utils/Utility.h"
namespace GUI
{
    TextureButton::TextureButton(Context& context, const sf::Texture& texture, sf::IntRect normal, sf::IntRect selected, sf::IntRect pressed)
    : Button(context)
    , mTexture(texture)
    , mNormalRect(normal)
    , mSelectedRect(selected)
    , mPressedRect(pressed)
    , mButton()
    { 
        changeTexture(Button::Normal);
    }

    sf::FloatRect TextureButton::getGlobalBounds() const
    {
        return sf::Transformable::getTransform().transformRect(mButton.getGlobalBounds());
    }
    
    void TextureButton::changeTexture(Button::Type buttonType)
    {
        switch (buttonType)
        {
            case Normal:
                mButton = sf::Sprite(mTexture, mNormalRect);
                break;
            case Selected:
                mButton = sf::Sprite(mTexture, mSelectedRect);
                break;
            case Pressed:
                mButton = sf::Sprite(mTexture, mPressedRect);
                break;
        }
        Utility::centerOrigin(mButton);
    }
    
    void TextureButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= sf::Transformable::getTransform();
        target.draw(mButton, states);
    }
}