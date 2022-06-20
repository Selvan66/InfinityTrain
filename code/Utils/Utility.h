/** @file Utility.h */
#pragma once

#include <cmath>

#include "Player/Player.h"
#include "Objects/Nodes/SceneNode.h"

namespace Utility
{

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOrigin(sf::Shape& shape);
float length(sf::Vector2f vector);
float distance(const SceneNode& lhs, const SceneNode& rhs);
std::string timeToString(unsigned long long time);

std::string toString(Player::Output key);
Player::Output toKey(std::string key);


template <typename T, typename P>
T* safeCasting(P* cast)
{
    assert(dynamic_cast<T*>(cast) != nullptr);
    return static_cast<T*>(cast);
}

}