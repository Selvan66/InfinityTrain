/** @file TextureButton.h */
#pragma once

#include "Gui/Button.h"

class TextureButton : public Button {
public:
  explicit TextureButton(Context &context);
  void setTextures(const sf::Texture &texture, sf::IntRect normal,
                   sf::IntRect selected, sf::IntRect pressed);

protected:
  virtual sf::FloatRect getGlobalBounds() const override;
  virtual void changeTexture(Button::Type buttonType) override;
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

private:
  sf::Sprite mNormalButton;
  sf::Sprite mSelectedButton;
  sf::Sprite mPressedButton;
  sf::Sprite mButton;
};