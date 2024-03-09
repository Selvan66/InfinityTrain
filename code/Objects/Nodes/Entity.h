/** @file Entity.h */
#pragma once

#include "Objects/Nodes/SceneNode.h"

class Entity : public SceneNode {
public:
  Entity();
  explicit Entity(int hitpoints);
  void setVelocity(sf::Vector2f velocity);
  void setVelocity(float vx, float vy);
  void accelerate(sf::Vector2f velocity);
  void accelerate(float vx, float vy);
  void setHitpoints(int hitpoints);
  sf::Vector2f getVelocity() const;
  int getHitpoints() const;
  void destroy();
  bool heal(int points);
  bool damageFromPos(int points, sf::Vector2f pos);

  virtual bool damage(int points);
  virtual void remove();
  virtual bool isDestroyed() const override;

protected:
  virtual void updateCurrent(sf::Time dt, CommandQueue&) override;

private:
  sf::Vector2f mVelocity;
  int mHitpoints;
};