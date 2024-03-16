/** @file Money.cpp */
#include "Objects/Nodes/Pickup/Money.h"
#include "Objects/Nodes/PlayerNode.h"

Money::Money(Context& context, unsigned int value)
  : Pickup(context), mValue(value) {
  Command command;
  command.category = Category::Player;
  command.action =
    derivedAction<PlayerNode>([this](PlayerNode& player, sf::Time) {
      if (player.updateStat(Stats::Money, static_cast<int>(mValue)))
        this->destroy();
    });

  Pickup::setTexture(TexturesID::Money);
  Pickup::setCommand(command);
  Pickup::setLabel(std::to_string(value) + "$");
}
