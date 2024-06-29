/** @file Interactable.h */
#pragma once

#include "Objects/Nodes/Entity.h"

class Interactable : public Entity {
public:
  Interactable();
  void setDistance(float distance);
  float getDistance() const;

  virtual void interact() = 0;

  virtual unsigned int getCategory() const override;

private:
  float mDistance;
};
