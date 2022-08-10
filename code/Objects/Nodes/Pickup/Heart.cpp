/** @file Heart.cpp */
#include "Objects/Nodes/Pickup/Heart.h"
#include "Objects/Nodes/PlayerNode.h"

Heart::Heart(Context& context, int value)
: Pickup(context)
, mValue(value)
{
    Interactable::setDistance(50.f);
    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([this](PlayerNode& player, sf::Time) {
        this->use(player);
    });

    Pickup::setTexture(TexturesID::Heart);
    Pickup::setCommand(command);
    Pickup::addText(std::to_string(value) + "HP");
}

bool Heart::use(PlayerNode& player)
{
    if (player.updateStat(Stats::Lives, mValue))
    {
        this->destroy();
        return true;
    }
    return false;
}