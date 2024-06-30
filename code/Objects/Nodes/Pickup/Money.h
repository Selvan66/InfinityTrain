/** @file Money.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class Money : public Pickup {
public:
  Money(Context& context, unsigned int value);

  virtual std::string getName() const override;

private:
  unsigned int mValue;
};
