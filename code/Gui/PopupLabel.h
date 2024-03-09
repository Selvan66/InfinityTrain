/** @file PopupLabel.h */
#pragma once

#include "App/Context.h"

class PopupLabel : public sf::Drawable, public sf::NonCopyable {
public:
  PopupLabel(Context& context);
  void setText(const std::string& text);
  void setObjectRect(const sf::FloatRect& objectRect);
  void handleEvent(const sf::Event& event);

protected:
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

private:
  void setBackgoundRect();
  void setLabelPos(const sf::Vector2f& pos);

private:
  sf::RectangleShape mBackground;
  bool mShow;
  sf::Text mText;
  sf::FloatRect mObjectRect;
  Context& mContext;
};