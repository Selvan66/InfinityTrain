/** @file HeadArmor.cpp */
#include "Objects/Nodes/Pickup/Equipment/HeadArmor.h"
#include "Objects/Nodes/PlayerNode.h"

HeadArmor::HeadArmor(Context& context, unsigned int durability)
: Pickup(context)
, mContext(context)
{
    Interactable::setDistance(50.f);
    
    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
        player.pickup(std::unique_ptr<HeadArmor>(new HeadArmor(context, Entity::getHitpoints())));
        this->destroy();
    });
    

    Entity::setHitpoints(durability);

    Pickup::setTexture(TexturesID::HeadArmor);
    Pickup::setCommand(command);
    Pickup::addText("Head Armor");
}

std::string HeadArmor::getDescription() const
{
    return "Head Armor\nDurability: " + std::to_string(Entity::getHitpoints());
}

bool HeadArmor::use(PlayerNode& player)
{
    player.pickup(std::unique_ptr<HeadArmor>(new HeadArmor(mContext, Entity::getHitpoints())));
    this->destroy();
    return true;
}