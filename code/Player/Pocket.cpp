/** @file Pocket.cpp */
#include "spdlog/spdlog.h"

#include "Player/Pocket.h"
#include "Utils/Utility.h"

Pocket::Pocket(Context& context)
  : Button(context), mContext(context), mBackground({32.f, 32.f}),
    mItem(nullptr), mPopupLabel(context) {
  mBackground.setOutlineThickness(1.5f);
  mBackground.setOutlineColor(sf::Color::White);
  mBackground.setFillColor(sf::Color::Transparent);
  Utility::centerOrigin(mBackground);
}

void Pocket::addItem(std::unique_ptr<Pickup> item) {
  spdlog::debug("Pocket::addItem | {}", item->getName());
  mItem = std::move(item);
}

std::unique_ptr<Pickup> Pocket::dropItem() {
  std::unique_ptr<Pickup> item = std::move(mItem);
  spdlog::debug("Pocket::dropItem | {}", item->getName());
  mItem = nullptr;
  mPopupLabel.setText("");
  return item;
}

bool Pocket::isItem() const { return mItem != nullptr; }

std::unique_ptr<Pickup>& Pocket::getItem() { return mItem; }

void Pocket::handleEvent(const sf::Event& event) {
  Button::handleEvent(event);
  mPopupLabel.handleEvent(event);
}

void Pocket::update() {
  Button::update();
  if (isItem()) {
    mPopupLabel.setText(mItem->getDescription());
    mPopupLabel.setObjectRect(getGlobalBounds());
  }
}

sf::FloatRect Pocket::getGlobalBounds() const {
  return sf::Transformable::getTransform().transformRect(
    mBackground.getGlobalBounds());
}

void Pocket::changeTexture(Button::Type buttonType) {
  switch (buttonType) {
  case Normal:
    mBackground.setFillColor(sf::Color::Transparent);
    break;
  case Selected:
    mBackground.setFillColor(sf::Color(255, 255, 255, 50));
    break;
  case Pressed:
    mBackground.setFillColor(sf::Color(255, 255, 255, 100));
    break;
  default:
    // Do nothing
    break;
  }
}

void Pocket::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= sf::Transformable::getTransform();
  target.draw(mBackground, states);
  if (isItem())
    mItem->drawCurrent(target, states);
  target.draw(mPopupLabel);
}
