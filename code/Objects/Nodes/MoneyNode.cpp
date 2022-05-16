/** @file MoneyNode.cpp */
#include "Objects/Nodes/MoneyNode.h"
#include "Objects/Nodes/PlayerNode.h"

MoneyNode::MoneyNode(Context& context, unsigned int value)
: Pickup(context, TexturesID::Money)
, mValue(value)
{
    Interactable::setDistance(50.f);
    Interactable::setText(std::to_string(value) + "$");

    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([value](PlayerNode& player, sf::Time) {
        player.increaseMoney(value);
    });

    Pickup::setCommand(command);
}
