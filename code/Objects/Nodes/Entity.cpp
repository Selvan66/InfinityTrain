/** @file Entity.cpp */
#include "Objects/Nodes/Entity.h"

Entity::Entity()
: mVelocity()
, mHitpoints(1)
{ }

Entity::Entity(int hitpoints)
: mVelocity()
, mHitpoints(hitpoints)
{ }

void Entity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;  
}

void Entity::setVelocity(float vx, float vy)
{
    mVelocity = sf::Vector2f(vx, vy);
}

void Entity::accelerate(sf::Vector2f velocity)
{
    mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
    mVelocity.x += vx;
    mVelocity.y += vy;
}

void Entity::setHitpoints(int hitpoints)
{
    mHitpoints = hitpoints;
}

sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}

int Entity::getHitpoints() const
{
    return mHitpoints;
}

void Entity::destroy()
{
    mHitpoints = 0;
}

bool Entity::heal(int points)
{
    assert(points > 0);
    int old_hitpoints = mHitpoints;
    mHitpoints = std::min(mHitpoints + points, 100);
    return old_hitpoints != mHitpoints;
}

bool Entity::damage(int points)
{
    assert(points > 0);
    int old_hitpoints = mHitpoints;
    mHitpoints = std::max(mHitpoints - points, 0);
    return old_hitpoints != mHitpoints;
}

void Entity::remove()
{
    destroy();
}

bool Entity::isDestroyed() const
{
    return mHitpoints <= 0;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue&)
{
    sf::Transformable::move(mVelocity * dt.asSeconds());
}