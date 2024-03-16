/** @file Utility.h */
#pragma once

#include <cmath>

#include "Objects/Nodes/SceneNode.h"
#include "Player/Player.h"

#define INF 0x0FFFFFFF

namespace Utility {

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOrigin(sf::Shape& shape);
float length(sf::Vector2f vector);
float toDegree(float radian);
float toRadian(float degree);
sf::Vector2f unitVector(sf::Vector2f vector);
float distance(const SceneNode& lhs, const SceneNode& rhs);
bool collision(const SceneNode& lhs, const SceneNode& rhs);
std::string timeToString(unsigned long long time);
bool areEqual(float lhs, float rhs);

sf::Vector2f getMousePos(sf::RenderWindow& window);

std::string toString(Player::Output key);
Player::Output toKey(std::string key);

template <typename... Args>
std::string stringFormat(const std::string& format, Args... args) {
  int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
  if (size_s <= 0) {
    throw std::runtime_error("Error during formatting.");
  }
  auto size = static_cast<size_t>(size_s);
  std::unique_ptr<char[]> buf(new char[size]);
  std::snprintf(buf.get(), size, format.c_str(), args...);
  return std::string(buf.get(), buf.get() + size - 1);
}

template <typename T, typename P> T* safeCasting(P* cast) {
  assert(dynamic_cast<T*>(cast) != nullptr);
  return static_cast<T*>(cast);
}

} // namespace Utility
