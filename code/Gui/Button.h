/** @file Button.h */
#pragma once

#include <functional>

#include "App/Context.h"
#include "Gui/Component.h"
class Button : public Component {
public:
  typedef std::function<void()> Callback;

  enum Type { Normal, Selected, Pressed };

public:
  explicit Button(Context &context);
  void setCallback(Callback callback);
  void setLeftClickCallback(Callback callback);
  void setRightClickCallback(Callback callback);

  virtual void handleEvent(const sf::Event &event) override;
  virtual void update() override;

protected:
  virtual sf::FloatRect getGlobalBounds() const = 0;
  virtual void changeTexture(Type buttonType);

private:
  Callback mLeftClickCallback;
  Callback mRightClickCallback;
  bool mIsSelected;
  bool mIsPressed;
  Context &mContext;
};