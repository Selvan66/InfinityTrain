/** @file Buyable.cpp */
#include "spdlog/spdlog.h"

#include "Objects/Nodes/Pickup/Buyable.h"
#include "Objects/Nodes/PlayerNode.h"

Buyable::Buyable(Context& context, int price, std::unique_ptr<Pickup> pickup)
  : Pickup(context), mPrice(price), mPickup(std::move(pickup)) {
  Command command;
  command.category = Category::Player;
  command.action =
    derivedAction<PlayerNode>([this](PlayerNode& player, sf::Time) {
      if (player.pay(mPrice)) {
        spdlog::debug("Buyable::Buyable | Command | Value {}", mPrice);
        player.pickup(mPickup->create());
        this->destroy();
      }
    });

  Pickup::setCommand(command);
  Pickup::setLabel(std::to_string(mPrice) + "$");
}

sf::FloatRect Buyable::getBoundingRect() const {
  return SceneNode::getWorldTransform().transformRect(
    mPickup->getBoundingRect());
}

void Buyable::drawCurrent(sf::RenderTarget& target,
                          sf::RenderStates states) const {
  mPickup->drawCurrent(target, states);
}
