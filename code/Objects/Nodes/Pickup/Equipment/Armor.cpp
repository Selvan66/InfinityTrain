/** @file Armor.cpp */
#include "Objects/Nodes/Pickup/Equipment/Armor.h"
#include "Objects/Nodes/PlayerNode.h"

Armor::Armor(Context& context, int durability)
: Pickup(context)
{
    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
        player.pickup(create());
        this->destroy();
    });
    Pickup::setCommand(command);
    Entity::setHitpoints(durability);
}

bool Armor::action(PlayerNode& player)
{
    player.pickup(create());
    return true;
}