/** @file Door.h */
#pragma once

#include "Effects/Animation.h"
#include "Objects/Nodes/Interactable.h"

struct Context;

class Door : public Interactable {
public:
  explicit Door(Context& context);
  void open();
  void close();
  bool isInteract() const;

  virtual void interact() override;

protected:
  virtual sf::FloatRect getBoundingRect() const override;
  virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
  virtual void drawCurrent(sf::RenderTarget& target,
                           sf::RenderStates states) const override;

private:
  bool mIsOpen;
  bool mInteract;
  sf::RectangleShape mBackground;
  Animation mAnimation;
};
