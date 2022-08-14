/** @file ChestArmor.cpp */
#include "Objects/Nodes/Pickup/Equipment/ChestArmor/ChestArmor.h"
#include "Objects/Nodes/PlayerNode.h"

ChestArmor::ChestArmor(Context& context, unsigned int durability)
: Pickup(context)
{
    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
        player.pickup(create());
        this->destroy();
    });
    
    Entity::setHitpoints(durability);

    Pickup::setTexture(TexturesID::ChestArmor);
    Pickup::setCommand(command);
    Pickup::setText("Chest Armor");
}

std::string ChestArmor::getDescription() const 
{
    return "Chest Armor\nDurability: " 
           + std::to_string(Entity::getHitpoints()) + 
           "\nSpeed: -50";
}

std::unordered_map<Stats::Type, int> ChestArmor::getStats() const 
{
    return {{Stats::Speed, -50}};
}

bool ChestArmor::use(PlayerNode& player)
{
    player.pickup(create());
    return true;
}

std::unique_ptr<Pickup> ChestArmor::create() const 
{
    return std::unique_ptr<Pickup>(new ChestArmor(Pickup::getContext(), Entity::getHitpoints()));
}