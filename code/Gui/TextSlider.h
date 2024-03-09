/** @file TextSlider.h */
#pragma once

#include <vector>

#include "Gui/TextureButton.h"

class TextSlider : public Component {
public:
  explicit TextSlider(Context& context);
  void addText(const std::string& text);
  std::string getCurrentText() const;
  void setCurrentText(const std::string& text);

  virtual void handleEvent(const sf::Event& event) override;
  virtual void update() override;

protected:
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

private:
  void setPosition(const sf::Vector2f& pos);
  void setNextText();
  void setPrevText();

private:
  Context& mContext;
  TextureButton mLeft;
  TextureButton mRight;
  std::vector<sf::Text> mTextArray;
  int mTextIndex;
  float mMaxTextWidth;
};