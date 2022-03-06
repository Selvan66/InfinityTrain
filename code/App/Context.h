/** @file Context.h */
#pragma once

#include <SFML/Graphics.hpp>

struct Context
{
    Context(sf::VideoMode mode)
    : mWindow(mode, "Infinity Train", sf::Style::Close)
    {}

    sf::RenderWindow mWindow;
};