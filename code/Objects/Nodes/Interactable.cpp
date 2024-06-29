/** @file Interactable.cpp */
#include "Objects/Nodes/Interactable.h"

Interactable::Interactable() : Entity(), mDistance(50) {}

void Interactable::setDistance(float distance) { mDistance = distance; }
float Interactable::getDistance() const { return mDistance; }

unsigned int Interactable::getCategory() const {
  return Category::Interactable;
}
