/** @file PopupLabel.cpp */
#include <SFML/Window.hpp>

#include "Gui/PopupLabel.h"
#include "Utils/Utility.h"

PopupLabel::PopupLabel(Context& context)
  : mBackground(), mShow(false),
    mText("", context.fonts.get(FontsID::PixelFont), 15), mObjectRect(),
    mContext(context) {}

void PopupLabel::setText(const std::string& text) {
  mText.setString(text);
  setBackgoundRect();
  Utility::centerOrigin(mText);
}

void PopupLabel::setObjectRect(const sf::FloatRect& objectRect) {
  mObjectRect = objectRect;
}

void PopupLabel::handleEvent(const sf::Event& event) {
  if (event.type == sf::Event::MouseMoved) {
    const auto& mouse = event.mouseMove;
    sf::Vector2f mousePos =
      mContext.window.mapPixelToCoords(sf::Vector2i(mouse.x, mouse.y));
    if (mObjectRect.contains(mousePos) && !mText.getString().isEmpty()) {
      mShow = true;
      setLabelPos(mousePos);
    } else {
      mShow = false;
    }
  }
}

void PopupLabel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (mShow && !mText.getString().isEmpty()) {
    target.draw(mBackground, states);
    target.draw(mText, states);
  }
}

void PopupLabel::setLabelPos(const sf::Vector2f& pos) {
  mBackground.setPosition(pos);
  const auto& bound = mBackground.getGlobalBounds();
  mText.setPosition(sf::Vector2f(bound.left + bound.width / 2.f,
                                 bound.top + bound.height / 2.f));
}

void PopupLabel::setBackgoundRect() {
  auto textBounds = mText.getLocalBounds();

  mBackground.setSize(
    sf::Vector2f(textBounds.width + 20, textBounds.height + 20));
  mBackground.setFillColor(sf::Color(60, 60, 60));
  auto bounds = mBackground.getLocalBounds();
  mBackground.setOrigin(bounds.left + bounds.width, bounds.top + bounds.height);
}
