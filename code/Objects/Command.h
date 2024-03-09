/** @file Command.h */
#pragma once

#include <cassert>
#include <functional>

#include <SFML/System.hpp>

#include "Objects/Category.h"

class SceneNode;

struct Command {
  Command();
  std::function<void(SceneNode&,
                     sf::Time)>
    action;
  unsigned int category;
};

template <typename Object,
          typename Function>
std::function<void(SceneNode&,
                   sf::Time)>
derivedAction(Function fn) {
  return [=](SceneNode& node,
             sf::Time dt) {
    assert(dynamic_cast<Object*>(
             &node) != nullptr);
    fn(static_cast<Object&>(node), dt);
  };
}