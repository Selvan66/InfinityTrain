/** @file Projectile.cpp **/
#include <array>

#include "App/Context.h"
#include "Objects/Nodes/Pickup/Equipment/Projectile.h"
#include "Utils/Utility.h"

static const std::array<
  ProjectileParam,
  Projectile::ProjectileCount>
  projectiles = {{
    {10,
     100.f,
     false,
     TexturesID::Arrow,
     sf::IntRect(0, 0, 32, 32),
     1,
     {32.f, 32.f}},
    {50,
     75.f,
     true,
     TexturesID::Rocket,
     sf::IntRect(0, 0, 32, 32),
     1,
     {32.f, 32.f}},
  }};

Projectile::Projectile(
  Context& context, Type type,
  Category::Type category)
  : mType(type),
    mCategoryType(category),
    mAnimation(
      context.textures.get(
        projectiles[type].animation),
      projectiles[type].animationRect),
    mTargetDirection(),
    mClosedEnemy(100000.f),
    mAttackCommand(), mFindCommand() {
  mAnimation.setFrameSize({32, 32});
  mAnimation.setNumFrames(
    projectiles[type].frameNum);
  mAnimation.setDuration(
    sf::seconds(0.5f));
  mAnimation.pause();

  if (category ==
      Category::AlliedProjectile) {
    mAttackCommand.category =
      Category::Enemy;
    mFindCommand.category =
      Category::Enemy;
  } else if (category ==
             Category::
               EnemyProjectile) {
    mAttackCommand.category =
      Category::Player;
    mFindCommand.category =
      Category::Player;
  } else {
    mAttackCommand.category =
      Category::None;
    mFindCommand.category =
      Category::None;
  }

  mAttackCommand.action = derivedAction<
    Entity>([&](Entity& entity,
                sf::Time) {
    if (Utility::collision(*this,
                           entity)) {
      entity.damageFromPos(
        projectiles[mType].damage,
        SceneNode::getWorldPosition());
      this->destroy();
    }
  });

  mFindCommand
    .action = derivedAction<Entity>(
    [&](Entity& entity, sf::Time) {
      float distance = Utility::length(
        entity.getWorldPosition() -
        SceneNode::getWorldPosition());
      if (distance < mClosedEnemy) {
        mClosedEnemy = distance;
        setDirection(
          entity.getWorldPosition());
      }
    });
}

void Projectile::setDirection(
  sf::Vector2f pos) {
  mTargetDirection =
    Utility::unitVector(
      pos -
      SceneNode::getWorldPosition());
}

int Projectile::getDamage(Type type) {
  return projectiles[type].damage;
}

unsigned int
Projectile::getCategory() const {
  return mCategoryType;
}

sf::FloatRect
Projectile::getBoundingRect() const {
  return SceneNode::getWorldTransform()
    .transformRect(
      mAnimation.getGlobalBounds());
}

void Projectile::updateCurrent(
  sf::Time dt, CommandQueue& commands) {
  Entity::updateCurrent(dt, commands);
  mAnimation.update(dt);
  commands.push(mAttackCommand);

  if (projectiles[mType].guide)
    commands.push(mFindCommand);

  const float approachRate = 200.f;
  sf::Vector2f newVelocity =
    Utility::unitVector(
      approachRate * dt.asSeconds() *
        mTargetDirection +
      Entity::getVelocity());
  newVelocity *=
    projectiles[mType].speed;
  float angle = std::atan2(
    newVelocity.y, newVelocity.x);
  Transformable::setRotation(
    Utility::toDegree(angle));
  Entity::accelerate(newVelocity);
}

void Projectile::drawCurrent(
  sf::RenderTarget& target,
  sf::RenderStates states) const {
  target.draw(mAnimation, states);
}
