/** @file Weapon.cpp */
#include "Objects/Nodes/Pickup/Equipment/Weapon.h"
#include "Objects/Nodes/Enemy/Enemy.h"
#include "Objects/Nodes/PlayerNode.h"
#include "Utils/Utility.h"

static const std::array<
  WeaponParam, Weapon::WeaponCount>
  weapons = {{
    {"Knife",
     INF,
     10,
     sf::seconds(0.5f),
     TexturesID::Knife,
     sf::IntRect(0, 0, 160, 32),
     5,
     Projectile::None,
     {52.f, 52.f}},
    {"Sword",
     25,
     25,
     sf::seconds(0.3f),
     TexturesID::Weapons,
     sf::IntRect(0, 64, 160, 32),
     5,
     Projectile::None,
     {64.f, 64.f}},
    {"Bow",
     10,
     Projectile::getDamage(
       Projectile::Arrow),
     sf::seconds(0.5f),
     TexturesID::Weapons,
     sf::IntRect(0, 0, 192, 64),
     12,
     Projectile::Arrow,
     {64.f, 64.f}},
    {"Bazooka",
     5,
     Projectile::getDamage(
       Projectile::Rocket),
     sf::seconds(0.5f),
     TexturesID::Bazooka,
     sf::IntRect(0, 0, 32, 32),
     1,
     Projectile::Rocket,
     {64.f, 64.f}},
  }};

Weapon::Weapon(Context& context,
               Type type)
  : Weapon(context, type,
           weapons[type].ammos) {}

Weapon::Weapon(Context& context,
               Type type, int ammos)
  : Pickup(context), mAttackCommand(),
    mUse(false), mAttacking(false),
    mType(type),
    mElapsed(weapons[type].duration +
             sf::seconds(1)),
    mAnimation(
      context.textures.get(
        weapons[type].animation),
      weapons[type].animationRect) {
  mAnimation.setFrameSize({32, 32});
  mAnimation.setNumFrames(
    weapons[type].frameNum);
  mAnimation.setDuration(
    weapons[type].duration);
  mAnimation.pause();

  if (weapons[type].projectile ==
      Projectile::None) {
    mAttackCommand.category =
      Category::Enemy;
    mAttackCommand.action =
      derivedAction<Enemy>(
        [&](Enemy& enemy, sf::Time) {
          if (Utility::collision(*this,
                                 enemy))
            enemy.damageFromPos(
              weapons[mType].damage,
              SceneNode::
                getWorldPosition());
        });
  } else {
    mAttackCommand.category =
      Category::Battlefield;
    mAttackCommand
      .action = [&](SceneNode& node,
                    sf::Time) {
      auto projectile =
        std::make_unique<Projectile>(
          Pickup::getContext(),
          weapons[mType].projectile,
          Category::AlliedProjectile);
      projectile->setPosition(
        SceneNode::getWorldPosition());
      projectile->setDirection(
        Utility::getMousePos(
          context.window));
      node.attachChild(
        std::move(projectile));
    };
  }

  Entity::setHitpoints(ammos);
}

void Weapon::use() { mUse = true; }

sf::Vector2f Weapon::getSize() const {
  return weapons[mType].size;
}

unsigned int
Weapon::getCategory() const {
  return Pickup::getCategory() |
         Category::Weapon;
}

std::string
Weapon::getDescription() const {
  std::stringstream ss;
  ss << weapons[mType].name << '\n';
  ss << "Damage: "
     << weapons[mType].damage << '\n';
  ss << "Ammos: "
     << (Entity::getHitpoints() == INF
           ? "INF"
           : std::to_string(
               Entity::getHitpoints()))
     << '\n';
  ss << "Duration: "
     << weapons[mType]
          .duration.asSeconds()
     << "s";
  return ss.str();
}

std::unordered_map<Stats::Type, int>
Weapon::getStats() const {
  return {{Stats::Attack,
           weapons[mType].damage}};
}

std::unique_ptr<Pickup>
Weapon::create() const {
  return std::unique_ptr<Pickup>(
    new Weapon(Pickup::getContext(),
               mType,
               Entity::getHitpoints()));
}

sf::FloatRect
Weapon::getBoundingRect() const {
  return SceneNode::getWorldTransform()
    .transformRect(
      mAnimation.getGlobalBounds());
}

void Weapon::updateCurrent(
  sf::Time dt, CommandQueue& commands) {
  Pickup::updateCurrent(dt, commands);
  mElapsed += dt;
  if (mElapsed >=
      weapons[mType].duration) {
    if (mUse) {
      mAttacking = true;
      mElapsed = sf::Time::Zero;
      mAnimation.play();
    }
  }
  mUse = false;

  if (mAttacking &&
      (mElapsed >=
       (weapons[mType].duration /
        3.f))) {
    mAttacking = false;
    commands.push(mAttackCommand);
    if (Entity::getHitpoints() != INF)
      Entity::damage(1);
  }

  mAnimation.update(dt);
  if (mAnimation.isFinished()) {
    mAnimation.restart();
    mAnimation.update(dt);
    mAnimation.pause();
  }
}

void Weapon::drawCurrent(
  sf::RenderTarget& target,
  sf::RenderStates states) const {
  target.draw(mAnimation, states);
}
