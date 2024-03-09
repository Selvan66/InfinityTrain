/** @file Projectile.h **/
#pragma once

#include "Effects/Animation.h"
#include "Objects/Nodes/Entity.h"
#include "Utils/ResourceIdentifiers.h"

class Projectile : public Entity {
public:
  enum Type {
    Arrow,
    Rocket,
    ProjectileCount,
    None,
  };

public:
  Projectile(Context& context,
             Type type,
             Category::Type category);
  void setDirection(sf::Vector2f pos);

  static int getDamage(Type type);

  virtual unsigned int
  getCategory() const override;
  virtual sf::FloatRect
  getBoundingRect() const override;

private:
  virtual void updateCurrent(
    sf::Time dt,
    CommandQueue& commands) override;
  virtual void
  drawCurrent(sf::RenderTarget& target,
              sf::RenderStates states)
    const override;

private:
  Type mType;
  Category::Type mCategoryType;
  Animation mAnimation;
  sf::Vector2f mTargetDirection;
  float mClosedEnemy;
  Command mAttackCommand;
  Command mFindCommand;
};

struct ProjectileParam {
  const int damage;
  const float speed;
  const bool guide;
  const TexturesID animation;
  const sf::IntRect animationRect;
  const size_t frameNum;
  sf::Vector2f size;
};
