/** @file TextButton.cpp */
#include "Gui/TextButton.h"
#include "Utils/Utility.h"

TextButton::TextButton(Context& context)
  : Button(context), mText("", context.fonts.get(FontsID::PixelFont), 60) {
  mText.setOutlineThickness(2.f);
  mText.setOutlineColor(sf::Color(0, 0, 0));
  changeTexture(Normal);
}

void TextButton::setText(const std::string& text) {
  mText.setString(text);
  Utility::centerOrigin(mText);
}

sf::FloatRect TextButton::getGlobalBounds() const {
  return sf::Transformable::getTransform().transformRect(
    mText.getGlobalBounds());
}

void TextButton::changeTexture(Button::Type buttonType) {
  sf::Color color;
  switch (buttonType) {
  case Normal:
    color = sf::Color(255, 255, 255);
    break;
  case Selected:
    color = sf::Color(255, 80, 80);
    break;
  case Pressed:
    color = sf::Color(255, 0, 0);
    break;
  default:
    // Do nothing
    break;
  }
  mText.setFillColor(color);
}

void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= sf::Transformable::getTransform();
  target.draw(mText, states);
}
