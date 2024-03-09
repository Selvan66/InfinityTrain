/** @file Potion.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class PlayerNode;

class Potion : public Pickup {
public:
  Potion(Context& context, unsigned int value);

  virtual std::string getDescription() const override;
  virtual bool action(PlayerNode& player) override;

protected:
  virtual std::unique_ptr<Pickup> create() const override;

private:
  unsigned int mValue;
  std::string mDescription;
};