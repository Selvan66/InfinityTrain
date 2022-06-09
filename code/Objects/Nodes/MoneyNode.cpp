/** @file MoneyNode.cpp */
#include "Objects/Nodes/MoneyNode.h"
#include "Objects/Nodes/PlayerNode.h"

MoneyNode::MoneyNode(Context& context, unsigned int value)
: Pickup(context, TexturesID::Money)
, mValue(value)
{
    Interactable::setDistance(50.f);

    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
        player.increaseMoney(mValue);
        this->destroy();
    });

    Pickup::setCommand(command);
}
