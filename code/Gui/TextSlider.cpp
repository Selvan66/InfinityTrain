/** @file TextSlider.cpp */
#include "Gui/TextSlider.h"
#include "Utils/Exceptions/bad_argument.h"
#include "Utils/Utility.h"

TextSlider::TextSlider(Context& context)
  : mContext(context), mLeft(context), mRight(context), mTextArray(),
    mTextIndex(-1), mMaxTextWidth(0) {
  mLeft.setTextures(context.textures.get(TexturesID::Gui),
                    sf::IntRect(0, 0, 60, 60), sf::IntRect(61, 0, 60, 60),
                    sf::IntRect(121, 0, 60, 60));

  mLeft.rotate(180);
  mLeft.setCallback([this]() { this->setPrevText(); });

  mRight.setTextures(context.textures.get(TexturesID::Gui),
                     sf::IntRect(0, 0, 60, 60), sf::IntRect(61, 0, 60, 60),
                     sf::IntRect(121, 0, 60, 60));

  mRight.setCallback([this]() { this->setNextText(); });
}

void TextSlider::addText(const std::string& text) {
  sf::Text newText(text, mContext.fonts.get(FontsID::PixelFont), 50);
  newText.setOutlineThickness(2.f);
  newText.setOutlineColor(sf::Color(0, 0, 0));
  Utility::centerOrigin(newText);
  float width = newText.getGlobalBounds().width;
  mMaxTextWidth = width > mMaxTextWidth ? width : mMaxTextWidth;
  mTextArray.push_back(newText);
  mTextIndex = 0;
}

std::string TextSlider::getCurrentText() const {
  assert(mTextIndex != -1);
  return mTextArray[static_cast<size_t>(mTextIndex)].getString();
}

void TextSlider::setCurrentText(const std::string& text) {
  assert(mTextIndex != -1);
  for (size_t i = 0; i < mTextArray.size(); ++i) {
    if (mTextArray[i].getString() == text) {
      mTextIndex = static_cast<int>(i);
      return;
    }
  }

  throw Except::bad_argument()
    .add("Text Slider")
    .add("Not found text in mTextArray");
}

void TextSlider::handleEvent(const sf::Event& event) {
  mLeft.handleEvent(event);
  mRight.handleEvent(event);
}

void TextSlider::update() {
  mLeft.update();
  mRight.update();

  setPosition(sf::Transformable::getPosition());
}

// Apply after addText()
void TextSlider::setPosition(const sf::Vector2f& pos) {
  mLeft.setPosition(-mMaxTextWidth / 1.5f, 0);
  mRight.setPosition(mMaxTextWidth / 1.5f, 0);
  mLeft.move(pos);
  mRight.move(pos);
}

void TextSlider::setNextText() {
  if (static_cast<size_t>(mTextIndex) < (mTextArray.size() - 1))
    ++mTextIndex;
}

void TextSlider::setPrevText() {
  if (mTextIndex > 0)
    --mTextIndex;
}

void TextSlider::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= sf::Transformable::getTransform();
  if (mTextIndex != -1) {
    target.draw(mLeft);
    target.draw(mRight);
    target.draw(mTextArray[static_cast<size_t>(mTextIndex)], states);
  }
}
