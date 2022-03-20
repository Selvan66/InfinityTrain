/** @file Utility.h */
#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

#include "App/Player.h"

namespace Utility
{

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOrigin(sf::Shape& shape);

std::string toString(Player::output key);
Player::output toKey(std::string key);

}