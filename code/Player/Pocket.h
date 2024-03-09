/** @file Pocket.h */
#pragma once

#include "App/Context.h"
#include "Gui/Button.h"
#include "Gui/PopupLabel.h"
#include "Objects/Nodes/Pickup/Pickup.h"

class Pocket : public Button {
public:
  explicit Pocket(Context &context);

  void addItem(std::unique_ptr<Pickup> item);
  std::unique_ptr<Pickup> dropItem();
  bool isItem() const;
  std::unique_ptr<Pickup> &getItem();

  virtual void handleEvent(const sf::Event &event) override;
  virtual void update() override;

protected:
  virtual sf::FloatRect getGlobalBounds() const override;
  virtual void changeTexture(Button::Type buttonType) override;
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

private:
  Context &mContext;
  sf::RectangleShape mBackground;
  std::unique_ptr<Pickup> mItem;
  PopupLabel mPopupLabel;
};