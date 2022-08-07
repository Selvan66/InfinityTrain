/** @file Potion.cpp */
#include "Objects/Nodes/Pickup/Potion.h"
#include "Objects/Nodes/PlayerNode.h"

Potion::Potion(Context& context, unsigned int value)
: Pickup(context)
, mValue(value)
{
    Interactable::setDistance(50.f);
    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
        player.pickup(std::unique_ptr<Potion>(new Potion(context, mValue)));
        this->destroy();
    });

    Pickup::setTexture(TexturesID::Potion);
    Pickup::setCommand(command);
    Pickup::addText(std::to_string(value) + "HP");
    Pickup::addDescription("Heal " + std::to_string(value) + "HP");
}

bool Potion::use(PlayerNode& player)
{
    if (player.updateStat(Stats::Lives, mValue))
    {
        this->destroy();
        return true;
    }
    return false;
}