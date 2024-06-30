/** @file Heart.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class Heart : public Pickup {
public:
  Heart(Context& context, unsigned int value);

  virtual std::string getName() const override { return "Heart"; }

private:
  unsigned int mValue;
};
