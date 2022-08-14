/** @file HeadArmor.cpp */
#include "Objects/Nodes/Pickup/Equipment/HeadArmor/HeadArmor.h"
#include "Objects/Nodes/PlayerNode.h"

HeadArmor::HeadArmor(Context& context, unsigned int durability)
: Pickup(context)
{    
    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
        player.pickup(create());
        this->destroy();
    });
    
    Entity::setHitpoints(durability);

    Pickup::setTexture(TexturesID::HeadArmor);
    Pickup::setCommand(command);
    Pickup::setText("Head Armor");
}

std::string HeadArmor::getDescription() const
{
    return "Head Armor\nDurability: " 
           + std::to_string(Entity::getHitpoints()) + 
           "\nSpeed: -50";
}

std::unordered_map<Stats::Type, int> HeadArmor::getStats() const 
{
    return {{Stats::Speed, -50}};
}

bool HeadArmor::use(PlayerNode& player)
{
    player.pickup(create());
    return true;
}

std::unique_ptr<Pickup> HeadArmor::create() const 
{
    return std::unique_ptr<Pickup>(new HeadArmor(Pickup::getContext(), Entity::getHitpoints()));
}