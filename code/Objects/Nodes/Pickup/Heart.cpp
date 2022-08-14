/** @file Heart.cpp */
#include "Objects/Nodes/Pickup/Heart.h"
#include "Objects/Nodes/PlayerNode.h"

Heart::Heart(Context& context, int value)
: Pickup(context)
, mValue(value)
{
    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([this](PlayerNode& player, sf::Time) {
        if (player.updateStat(Stats::Lives, mValue))
            this->destroy();
    });

    Pickup::setTexture(TexturesID::Heart);
    Pickup::setCommand(command);
    Pickup::setText(std::to_string(value) + "HP");
}