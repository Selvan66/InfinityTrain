/** @file Category.h */
#pragma once

namespace Category {

enum Type {
  None = 0,
  Player = 1 << 0,
  Battlefield = 1 << 1,
  Floor = 1 << 2,
  Interactable = 1 << 3,
  Enemy = 1 << 4,
  Helmet = 1 << 5,
  Chestplate = 1 << 6,
  Boots = 1 << 7,
  Weapon = 1 << 8,
  Special = 1 << 9,
  AlliedProjectile = 1 << 10,
  EnemyProjectile = 1 << 11,
};

} // namespace Category