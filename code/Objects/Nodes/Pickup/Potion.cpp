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
        player.pickup(create());
        this->destroy();
    });

    Pickup::setTexture(TexturesID::Potion);
    Pickup::setCommand(command);
    Pickup::setLabel(std::to_string(value) + "HP");
    Pickup::setName("Heal " + std::to_string(value) + " HP");
}

bool Potion::action(PlayerNode& player)
{
    if (player.updateStat(Stats::Lives, mValue))
        return true;
    return false;
}

std::unique_ptr<Pickup> Potion::create() const 
{
    return std::unique_ptr<Pickup>(new Potion(Pickup::getContext(), mValue));
}