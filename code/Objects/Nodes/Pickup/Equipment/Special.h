/** @file Special.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class Special : public Pickup {
public:
  enum Type {
    PortalGun,
    SpecialCount,
  };

public:
  Special(Context& context, Type type);
  Special(Context& context, Type type, int ammos);

  void use();

  virtual unsigned int getCategory() const override;
  virtual std::string getDescription() const override;
  virtual std::unordered_map<Stats::Type, int> getStats() const override;

protected:
  virtual std::unique_ptr<Pickup> create() const override;
  virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;

private:
  const Type mType;
  bool mUse;
  sf::Time mElapsed;
};

struct SpecialParam {
  const char* name;
  const int ammos;
  const sf::Time duration;
  const std::unordered_map<Stats::Type, int> stats;
  const TexturesID texture;
  const sf::IntRect textureRect;
  Command action;
};

void initSpecialsActions(Context& context);