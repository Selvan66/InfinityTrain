/** @file Heart.cpp */
#include "spdlog/spdlog.h"

#include "Objects/Nodes/Pickup/Heart.h"
#include "Objects/Nodes/PlayerNode.h"

Heart::Heart(Context& context, unsigned int value)
  : Pickup(context), mValue(value) {
  Command command;
  command.category = Category::Player;
  command.action =
    derivedAction<PlayerNode>([this](PlayerNode& player, sf::Time) {
      if (player.heal(mValue)) {
        spdlog::debug("Heart::Heart | Command | Value {}", mValue);
        this->destroy();
      }
    });

  Pickup::setTexture(TexturesID::Heart);
  Pickup::setCommand(command);
  Pickup::setLabel(std::to_string(value) + "HP");
}
