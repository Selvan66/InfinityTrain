/** @file Potion.cpp */
#include "Objects/Nodes/Pickup/Potion.h"
#include "Objects/Nodes/PlayerNode.h"

Potion::Potion(Context& context, unsigned int value)
: Pickup(context)
, mValue(value)
, mDescription("Heal " + std::to_string(value) + " HP")
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
}

std::string Potion::getDescription() const
{
    return mDescription;
}

bool Potion::use(PlayerNode& player)
{
    if (player.updateStat(Stats::Lives, mValue))
        return true;
    return false;
}