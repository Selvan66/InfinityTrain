/** @file Armor.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class Armor : public Pickup {
public:
  enum Type {
    HeavyBoots,
    LightBoots,
    HeavyChest,
    HeavyHelmet,
    ArmorCount
  };

public:
  Armor(Context& context, Type type);
  Armor(Context& context, Type type,
        int durability);

  virtual unsigned int
  getCategory() const override;
  virtual std::string
  getDescription() const override;
  virtual std::unordered_map<
    Stats::Type, int>
  getStats() const override;

protected:
  virtual std::unique_ptr<Pickup>
  create() const override;

private:
  const Type mType;
};

struct ArmorParam {
  const char* name;
  const int durability;
  const std::unordered_map<Stats::Type,
                           int>
    stats;
  const TexturesID texture;
  const sf::IntRect textureRect;
  const Category::Type type;
};