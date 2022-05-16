/** @file HeartNode.cpp */
#include "Objects/Nodes/HeartNode.h"
#include "Objects/Nodes/PlayerNode.h"

HeartNode::HeartNode(Context& context, int value)
: Pickup(context, TexturesID::Heart)
, mValue(value)
{
    Interactable::setDistance(50.f);
    Interactable::setText(std::to_string(value) + "HP");

    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([value](PlayerNode& player, sf::Time) {
        player.increaseLive(value);
    });

    Pickup::setCommand(command);
}
