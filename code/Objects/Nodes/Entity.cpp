/** @file Entity.cpp */
#include <cmath>

#include "Objects/Nodes/Entity.h"
#include "Utils/Utility.h"

Entity::Entity() : Entity(1) {}

Entity::Entity(int hitpoints) : mVelocity(), mHitpoints(hitpoints) {}

void Entity::setVelocity(sf::Vector2f velocity) { mVelocity = velocity; }

void Entity::setVelocity(float vx, float vy) {
  mVelocity = sf::Vector2f(vx, vy);
}

void Entity::accelerate(sf::Vector2f velocity) { mVelocity += velocity; }

void Entity::accelerate(float vx, float vy) {
  mVelocity.x += vx;
  mVelocity.y += vy;
}

void Entity::setHitpoints(int hitpoints) { mHitpoints = hitpoints; }

sf::Vector2f Entity::getVelocity() const { return mVelocity; }

int Entity::getHitpoints() const { return mHitpoints; }

void Entity::destroy() { mHitpoints = 0; }

bool Entity::heal(unsigned int points) {
  int old_hitpoints = mHitpoints;
  mHitpoints = std::min(mHitpoints + static_cast<int>(points), 100);
  return old_hitpoints != mHitpoints;
}

bool Entity::damageFromPos(int points, sf::Vector2f pos) {
  auto direction = Utility::unitVector(SceneNode::getWorldPosition() - pos);
  accelerate(direction * 1000.f);
  return damage(points);
}

bool Entity::damage(int points) {
  assert(points >= 0);
  mHitpoints -= points;
  return true;
}

void Entity::remove() { destroy(); }

bool Entity::isDestroyed() const { return mHitpoints <= 0; }

void Entity::updateCurrent(sf::Time dt, CommandQueue&) {
  mVelocity -= mVelocity * dt.asSeconds() * 10.f;
  if (Utility::length(mVelocity) < 5.f)
    mVelocity = sf::Vector2f(0, 0);

  auto velocity = mVelocity;
  if (!Utility::areEqual(velocity.x, 0.0) && Utility::areEqual(velocity.y, 0.0))
    velocity /= (float)std::sqrt(2.0);

  sf::Transformable::move(velocity * dt.asSeconds());
}
