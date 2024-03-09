/** @file TextureButton.cpp */
#include "Gui/TextureButton.h"
#include "Utils/Utility.h"

TextureButton::TextureButton(Context &context)
    : Button(context), mNormalButton(), mSelectedButton(), mPressedButton(),
      mButton() {}

void TextureButton::setTextures(const sf::Texture &texture, sf::IntRect normal,
                                sf::IntRect selected, sf::IntRect pressed) {
  mNormalButton = sf::Sprite(texture, normal);
  mSelectedButton = sf::Sprite(texture, selected);
  mPressedButton = sf::Sprite(texture, pressed);
  changeTexture(Button::Normal);
}

sf::FloatRect TextureButton::getGlobalBounds() const {
  return sf::Transformable::getTransform().transformRect(
      mButton.getGlobalBounds());
}

void TextureButton::changeTexture(Button::Type buttonType) {
  switch (buttonType) {
  case Normal:
    mButton = mNormalButton;
    break;
  case Selected:
    mButton = mSelectedButton;
    break;
  case Pressed:
    mButton = mPressedButton;
    break;
  }
  Utility::centerOrigin(mButton);
}

void TextureButton::draw(sf::RenderTarget &target,
                         sf::RenderStates states) const {
  states.transform *= sf::Transformable::getTransform();
  target.draw(mButton, states);
}