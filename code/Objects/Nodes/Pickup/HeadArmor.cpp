/** @file HeadArmor.cpp */
#include "Objects/Nodes/Pickup/HeadArmor.h"
#include "Objects/Nodes/PlayerNode.h"

HeadArmor::HeadArmor(Context& context)
: Pickup(context)
, mContext(context)
{
    Interactable::setDistance(50.f);
    
    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
        player.pickup(std::unique_ptr<HeadArmor>(new HeadArmor(context)));
        this->destroy();
    });
    
    Pickup::setTexture(TexturesID::HeadArmor);
    Pickup::setCommand(command);
    Pickup::addText("Head Armor");
    Pickup::addDescription("Head Armor");
}

bool HeadArmor::use(PlayerNode& player)
{
    player.pickup(std::unique_ptr<HeadArmor>(new HeadArmor(mContext)));
    this->destroy();
    return true;
}