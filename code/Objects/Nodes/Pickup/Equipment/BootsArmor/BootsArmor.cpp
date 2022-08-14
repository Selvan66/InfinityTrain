/** @file BootsArmor.cpp */
#include "Objects/Nodes/Pickup/Equipment/BootsArmor/BootsArmor.h"
#include "Objects/Nodes/PlayerNode.h"


BootsArmor::BootsArmor(Context& context, unsigned int durability)
: Pickup(context)
{
    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
        player.pickup(create());
        this->destroy();
    });
    
    Entity::setHitpoints(durability);

    Pickup::setTexture(TexturesID::BootsArmor);
    Pickup::setCommand(command);
    Pickup::setText("Boots Armor");
}

std::string BootsArmor::getDescription() const 
{
    return "Boots Armor\nDurability: " 
           + std::to_string(Entity::getHitpoints()) + 
           "\nSpeed: -50";
}

std::unordered_map<Stats::Type, int> BootsArmor::getStats() const 
{
    return {{Stats::Speed, -50}};
}

bool BootsArmor::use(PlayerNode& player)
{
    player.pickup(create());
    return true;
}

std::unique_ptr<Pickup> BootsArmor::create() const 
{
    return std::unique_ptr<Pickup>(new BootsArmor(Pickup::getContext(), Entity::getHitpoints()));
}
