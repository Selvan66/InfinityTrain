/** @file Utility.h */
#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

namespace Utility
{

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOrigin(sf::Shape& shape);

}