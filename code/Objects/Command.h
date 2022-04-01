/** @file Command.h */
#pragma once

#include <functional>
#include <cassert>

#include <SFML/System.hpp>

#include "Objects/Category.h"

class SceneNode;

struct Command
{
    Command();
    std::function<void(SceneNode&, sf::Time)> action;
    Category category;
};

Command::Command()
: action(),
category(Category::None)
{ }

template <typename Object, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
    return [=](SceneNode& node, sf::Time dt)
    {
        assert(dynamic_cast<Object*>(&node) != nullptr);
        fn(static_cast<Object&>(node), dt);
    };
}