/** @file ChestArmor.cpp */
#include "Objects/Nodes/Pickup/Equipment/ChestArmor.h"
#include "Objects/Nodes/PlayerNode.h"

static std::array<ArmorParam, ChestArmor::ChestCount> chests = 
{
    {
        { "Heavy", 150, { { Stats::Speed, -50 } }, TexturesID::ChestArmor, sf::IntRect(0, 0, 32, 32) },
    }
};

ChestArmor::ChestArmor(Context& context, size_t index)
: ChestArmor(context, index, chests[index].durability)
{ }

ChestArmor::ChestArmor(Context& context, size_t index, unsigned int durability)
: Armor(context, durability)
, mIndex(index)
{
    Pickup::setTexture(chests[index].texture);
    Pickup::setText(chests[index].name);
}

const std::unordered_map<Stats::Type, int>& ChestArmor::getStats() const 
{
    return chests[mIndex].stats;
}

std::unique_ptr<Pickup> ChestArmor::create() const 
{
    return std::unique_ptr<Pickup>(new ChestArmor(Pickup::getContext(), mIndex, Entity::getHitpoints()));
}