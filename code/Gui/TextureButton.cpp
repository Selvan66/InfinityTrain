/** @file TextureButton.cpp */
#include "Gui/TextureButton.h"

namespace GUI
{
    TextureButton::TextureButton(Context& context, const sf::Texture& texture)
    : Button(context)
    , mTexture(texture)
    { }

    void TextureButton::setRectNormal(const sf::IntRect& rect)
    {
        mButtonSprite.setTexture(mTexture);
        mButtonSprite.setTextureRect(rect);
    }
}