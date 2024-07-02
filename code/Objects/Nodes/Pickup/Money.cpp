/** @file Money.cpp */
#include "spdlog/spdlog.h"

#include "Objects/Nodes/Pickup/Money.h"
#include "Objects/Nodes/PlayerNode.h"

Money::Money(Context& context, unsigned int value)
  : Pickup(context), mValue(value) {
  Command command;
  command.category = Category::Player;
  command.action =
    derivedAction<PlayerNode>([this](PlayerNode& player, sf::Time) {
      if (player.updateStat(Stats::Money, static_cast<int>(mValue))) {
        spdlog::debug("Money::Money | Command | Value {}", mValue);
        this->destroy();
      }
    });

  Pickup::setTexture(TexturesID::Money);
  Pickup::setCommand(command);
  Pickup::setLabel(std::to_string(value) + "$");
}

std::string Money::getName() const { return "Money"; }
