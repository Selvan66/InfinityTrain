/** @file Money.cpp */
#include "Objects/Nodes/Pickup/Money.h"
#include "Objects/Nodes/PlayerNode.h"

Money::Money(Context& context, unsigned int value)
: Pickup(context)
, mValue(value)
{
    Interactable::setDistance(50.f);

    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([this](PlayerNode& player, sf::Time) {
        this->use(player);
    });

    Pickup::setTexture(TexturesID::Money);
    Pickup::setCommand(command);
    Pickup::addText(std::to_string(value) + "$");
}

bool Money::use(PlayerNode& player)
{
    if (player.updateStat(Stats::Money, mValue))
    {
        this->destroy();
        return true;
    }
    return false;
}