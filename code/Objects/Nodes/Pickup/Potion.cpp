/** @file Potion.cpp */
#include "Objects/Nodes/Pickup/Potion.h"
#include "Objects/Nodes/PlayerNode.h"

Potion::Potion(Context& context, unsigned int value)
  : Pickup(context), mValue(value),
    mDescription("Heal " + std::to_string(value) + " HP") {
  Interactable::setDistance(50.f);
  Pickup::setTexture(TexturesID::Potion);
  Pickup::setLabel(std::to_string(value) + "HP");
}

std::string Potion::getDescription() const { return mDescription; }

bool Potion::action(PlayerNode& player) {
  spdlog::debug("Potion::action | Heal player by {}", mValue);
  return player.heal(mValue);
}

std::unique_ptr<Pickup> Potion::create() const {
  return std::unique_ptr<Pickup>(new Potion(Pickup::getContext(), mValue));
}
