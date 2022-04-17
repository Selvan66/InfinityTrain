/** @file Utility.h */
#pragma once

#include <cmath>

#include "App/Player.h"

namespace Utility
{

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOrigin(sf::Shape& shape);

std::string toString(Player::Output key);
Player::Output toKey(std::string key);

}