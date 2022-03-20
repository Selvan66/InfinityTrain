/** @file Player.h */
#pragma once

#include <variant>

#include <SFML/Graphics.hpp>


class Player
{
    public:
        typedef std::variant<sf::Mouse::Button, sf::Keyboard::Key> output;
};