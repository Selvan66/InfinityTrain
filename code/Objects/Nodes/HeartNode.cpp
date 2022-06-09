/** @file HeartNode.cpp */
#include "Objects/Nodes/HeartNode.h"
#include "Objects/Nodes/PlayerNode.h"

HeartNode::HeartNode(Context& context, int value)
: Pickup(context, TexturesID::Heart)
, mValue(value)
{
    Interactable::setDistance(50.f);
    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
        player.increaseLive(mValue);
        this->destroy();
    });

    Pickup::setCommand(command);
}