/** @file Component.h */
#pragma once

#include <SFML/Graphics.hpp>

class Component : public sf::Drawable,
                  public sf::Transformable,
                  public sf::NonCopyable {
public:
  Component();
  virtual void handleEvent(const sf::Event& event);
  virtual void update();
};