/** @file PlayerNode.cpp */
#include "spdlog/spdlog.h"

#include "Objects/Nodes/Interactable.h"
#include "Objects/Nodes/PlayerNode.h"
#include "Utils/Utility.h"

PlayerNode::PlayerNode(Context& context, PlayerInfo& playerInfo)
  : Entity(playerInfo.stats.getStat(Stats::Lives)), mContext(context),
    mPlayerInfo(playerInfo), mFireCommand(), mIsFire(false), mInteractCommand(),
    mIsInteract(false), mSpecialCommand(), mIsSpecial(false),
    mAnimation(context.textures.get(TexturesID::Finn),
               sf::IntRect(9 * 32, 0, 6 * 32, 32)),
    mWeapon(nullptr), mSpecial(nullptr), mDamageDuration(sf::seconds(0.3f)),
    mIsWeaponEquip(false), mIsSpecialEquip(false) {
  mFireCommand.category = Category::Battlefield;
  mFireCommand.action = [&](SceneNode&, sf::Time) {
    if (mWeapon != nullptr) {
      spdlog::trace("PlayerNode::PlayerNode | Use weapon {}",
                    mWeapon->getName());
      mWeapon->use();
    }
  };

  mInteractCommand.category = Category::Interactable;
  mInteractCommand.action =
    derivedAction<Interactable>([&](Interactable& interactable, sf::Time) {
      if (Utility::distance(*this, interactable) < interactable.getDistance()) {
        spdlog::trace("PlayerNode::PlayerNode | Interact with category {}",
                      static_cast<int>(interactable.getCategory()));
        interactable.interact();
      }
    });

  mSpecialCommand.category = Category::Battlefield;
  mSpecialCommand.action = [&](SceneNode&, sf::Time) {
    if (mSpecial != nullptr) {
      spdlog::trace("PlayerNode::PlayerNode | Use special {}",
                    mSpecial->getName());
      mSpecial->use();
    }
  };

  mAnimation.setFrameSize({32, 32});
  mAnimation.setNumFrames(6);
  mAnimation.setDuration(sf::seconds(0.4f));
  mAnimation.setRepeating(true);
  mAnimation.setScale({2.5f, 2.5f});
}

void PlayerNode::makeAction(Action action) {
  switch (action) {
  case MoveUp:
    Entity::accelerate(
      {0.f, static_cast<float>(-mPlayerInfo.stats.getStat(Stats::Speed))});
    break;
  case MoveDown:
    Entity::accelerate(
      {0.f, static_cast<float>(mPlayerInfo.stats.getStat(Stats::Speed))});
    break;
  case MoveLeft:
    Entity::accelerate(
      {static_cast<float>(-mPlayerInfo.stats.getStat(Stats::Speed)), 0.f});
    break;
  case MoveRight:
    Entity::accelerate(
      {static_cast<float>(mPlayerInfo.stats.getStat(Stats::Speed)), 0.f});
    break;
  case Fire:
    fire();
    break;
  case Interact:
    interact();
    break;
  case Specials:
    special();
    break;
  default:
    // Do nothing
    break;
  }
}

void PlayerNode::pickup(std::unique_ptr<Pickup> pickup) {
  if (mPlayerInfo.equipment.canBeEquipped(pickup)) {
    spdlog::debug("PlayerNode::pickup | Move item {} to equipment",
                  pickup->getName());
    mPlayerInfo.equipment.equip(std::move(pickup));
  } else {
    spdlog::debug("PlayerNode::pickup | Move item {} to backpack",
                  pickup->getName());
    mPlayerInfo.backpack.addItemToBackpack(std::move(pickup));
  }
}

bool PlayerNode::pay(int price) {
  if (mPlayerInfo.stats.getStat(Stats::Money) >= price) {
    mPlayerInfo.stats.updateStat(Stats::Money, -price);
    return true;
  }

  return false;
}

bool PlayerNode::updateStat(Stats::Type stat, int value) {
  return mPlayerInfo.stats.updateStat(stat, value);
}

unsigned int PlayerNode::getCategory() const { return Category::Player; }

sf::FloatRect PlayerNode::getBoundingRect() const {
  return SceneNode::getWorldTransform().transformRect(
    mAnimation.getGlobalBounds());
}

bool PlayerNode::damage(int points) {
  float damage = static_cast<float>(points);
  float fpoints = static_cast<float>(points);
  mDamageDuration = sf::Time::Zero;
  auto& eq = mPlayerInfo.equipment;
  if (eq.isItem(Equipment::Head)) {
    eq.getItem(Equipment::Head)->damage(static_cast<int>(points * 0.35));
    damage -= fpoints * 0.35f;
  }
  if (eq.isItem(Equipment::Chest)) {
    eq.getItem(Equipment::Chest)->damage(static_cast<int>(points * 0.45));
    damage -= fpoints * 0.45f;
  }
  if (eq.isItem(Equipment::Boots)) {
    eq.getItem(Equipment::Boots)->damage(static_cast<int>(points * 0.2));
    damage -= fpoints * 0.2f;
  }

  int idamage = static_cast<int>(damage);
  spdlog::debug("PlayerNode::damage | Get {} hitpoints", idamage);

  return Entity::damage(idamage);
}

void PlayerNode::drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const {
  target.draw(mAnimation, states);
}

void PlayerNode::updateCurrent(sf::Time dt, CommandQueue& commands) {
  if (mIsFire) {
    spdlog::trace("PlayerNode::updateCurrent | Fire Command");
    commands.push(mFireCommand);
    mIsFire = false;
  }
  if (mIsInteract) {
    spdlog::trace("PlayerNode::updateCurrent | Interact Command");
    commands.push(mInteractCommand);
    mIsInteract = false;
  }
  if (mIsSpecial) {
    spdlog::trace("PlayerNode::updateCurrent | Special Command");
    commands.push(mSpecialCommand);
    mIsSpecial = false;
  }

  updateAnimation(dt);
  updateEquipedWeapon();
  updateEquipedSpecial();
  updateStats();
  updateWeaponPosition();
  Entity::updateCurrent(dt, commands);
}

void PlayerNode::fire() { mIsFire = true; }

void PlayerNode::interact() { mIsInteract = true; }

void PlayerNode::special() { mIsSpecial = true; }

void PlayerNode::updateAnimation(sf::Time dt) {
  mDamageDuration += dt;
  if (mDamageDuration < sf::seconds(0.3f))
    mAnimation.setColor(sf::Color::Red);
  else
    mAnimation.setColor(sf::Color::White);

  sf::Vector2f velocity = Entity::getVelocity();
  if (Utility::areEqual(velocity.x, 0.f) &&
      Utility::areEqual(velocity.y, 0.f)) {
    mAnimation.restart();
    mAnimation.update(dt);
    mAnimation.pause();
  } else {
    mAnimation.play();
  }

  if (Utility::getMousePos(mContext.window).x <
      SceneNode::getWorldPosition().x) {
    sf::Transformable::setScale(-1.f, 1.f);
    mAnimation.setReversed(true); // TODO: Last player
                                  // texture must be like
                                  // first one
  } else {
    sf::Transformable::setScale(1.f, 1.f);
    mAnimation.setReversed(false);
  }

  mAnimation.update(dt);
}

void PlayerNode::updateEquipedWeapon() {
  bool leftHandEq = mPlayerInfo.equipment.isItem(Equipment::LeftHand);
  bool weaponOnScreen =
    mWeapon != nullptr ? SceneNode::isChildAttach(*mWeapon) : false;

  // Delete on screen
  if (mIsWeaponEquip && weaponOnScreen && !leftHandEq) {
    spdlog::debug("PlayerNode::updateEquipedWeapon | Delete on screen");
    mWeapon->destroy();
    mIsWeaponEquip = false;
    mWeapon = nullptr;
    return;
  }

  // Delete in hand
  if (mIsWeaponEquip && !weaponOnScreen && leftHandEq) {
    spdlog::debug("PlayerNode::updateEquipedWeapon | Delete in hand");
    mPlayerInfo.equipment.getItem(Equipment::LeftHand)->destroy();
    mIsWeaponEquip = false;
    mWeapon = nullptr;
    return;
  }

  // Update
  if (weaponOnScreen && leftHandEq && mIsWeaponEquip) {
    spdlog::trace("PlayerNode::updateEquipedWeapon | Update");
    mPlayerInfo.equipment.getItem(Equipment::LeftHand)
      ->setHitpoints(mWeapon->getHitpoints());
    return;
  }

  // Create
  if (!mIsWeaponEquip && leftHandEq && !weaponOnScreen) {
    spdlog::debug("PlayerNode::updateEquipedWeapon | Create");
    auto weapon_ptr =
      mPlayerInfo.equipment.getItem(Equipment::LeftHand)->create();
    mWeapon = dynamic_cast<Weapon*>(weapon_ptr.get());
    mWeapon->setDistance(0.f);
    sf::Vector2f size = {mWeapon->getSize().x / 32.f,
                         mWeapon->getSize().y / 32.f};
    mWeapon->setScale(size);
    SceneNode::attachChild(std::move(weapon_ptr));
    mIsWeaponEquip = true;
    return;
  }
}

void PlayerNode::updateEquipedSpecial() {
  bool rightHandEq = mPlayerInfo.equipment.isItem(Equipment::RightHand);
  bool specialOnScreen =
    mSpecial != nullptr ? SceneNode::isChildAttach(*mSpecial) : false;

  // Delete on screen
  if (mIsSpecialEquip && specialOnScreen && !rightHandEq) {
    spdlog::debug("PlayerNode::updateEquipedSpecial | Delete on screen");
    mSpecial->destroy();
    mIsSpecialEquip = false;
    mSpecial = nullptr;
    return;
  }

  // Delete on hand
  if (mIsSpecialEquip && !specialOnScreen && rightHandEq) {
    spdlog::debug("PlayerNode::updateEquipedSpecial | Delete on hand");
    mPlayerInfo.equipment.getItem(Equipment::RightHand)->setHitpoints(0);
    mIsSpecialEquip = false;
    mSpecial = nullptr;
    return;
  }

  // Update
  if (mIsSpecialEquip && specialOnScreen && rightHandEq) {
    spdlog::trace("PlayerNode::updateEquipedSpecial | Update");
    mPlayerInfo.equipment.getItem(Equipment::RightHand)
      ->setHitpoints(mSpecial->getHitpoints());
    return;
  }

  // Create
  if (!mIsSpecialEquip && !specialOnScreen && rightHandEq) {
    auto special_ptr =
      mPlayerInfo.equipment.getItem(Equipment::RightHand)->create();
    mSpecial = dynamic_cast<Special*>(special_ptr.get());
    mSpecial->setDistance(0.f);
    mSpecial->setPosition(-40.f, -40.f);
    SceneNode::attachChild(std::move(special_ptr));
    mIsSpecialEquip = true;
    return;
  }
}

void PlayerNode::updateStats() {
  auto& stats = mPlayerInfo.stats;
  auto& eq = mPlayerInfo.equipment;

  stats.setStat(Stats::Lives, Entity::getHitpoints());

  int armor = 0;
  if (eq.isItem(Equipment::Head))
    armor += eq.getItem(Equipment::Head)->getHitpoints();
  if (eq.isItem(Equipment::Chest))
    armor += eq.getItem(Equipment::Chest)->getHitpoints();
  if (eq.isItem(Equipment::Boots))
    armor += eq.getItem(Equipment::Boots)->getHitpoints();

  stats.setStat(Stats::Armor, armor);

  if (eq.isItem(Equipment::LeftHand))
    stats.setStat(Stats::Ammo, eq.getItem(Equipment::LeftHand)->getHitpoints());
  else
    stats.setStat(Stats::Ammo, 0);
}

void PlayerNode::updateWeaponPosition() {
  if (mWeapon != nullptr) {
    sf::Vector2f vec =
      Utility::getMousePos(mContext.window) - SceneNode::getWorldPosition();
    sf::FloatRect playerBounds = getBoundingRect();
    mWeapon->setPosition(std::min(playerBounds.width / 2.f,
                                  std::abs(vec.x) - std::abs(vec.x / 1000.f)),
                         std::min(playerBounds.height / 2.f,
                                  std::max(-40.f, vec.y - (vec.y / 1000.f))));
    mWeapon->setRotation(Utility::toDegree(std::atan2(vec.y, std::abs(vec.x))));
  }
}
