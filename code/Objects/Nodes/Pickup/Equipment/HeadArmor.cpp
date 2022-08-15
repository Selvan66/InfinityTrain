/** @file HeadArmor.cpp */
#include "Objects/Nodes/Pickup/Equipment/HeadArmor.h"
#include "Objects/Nodes/PlayerNode.h"

static std::array<ArmorParam, HeadArmor::HelmetCount> helmets = 
{
    {
        { "Heavy", 75, { { Stats::Speed, -25 } }, TexturesID::HeadArmor, sf::IntRect(0, 0, 32, 32) },
    }
};

HeadArmor::HeadArmor(Context& context, size_t index)
: HeadArmor(context, index, helmets[index].durability)
{ }

HeadArmor::HeadArmor(Context& context, size_t index, unsigned int durability)
: Armor(context, durability)
, mIndex(index)
{
    Pickup::setTexture(helmets[index].texture);
    Pickup::setText(helmets[index].name);
}

const std::unordered_map<Stats::Type, int>& HeadArmor::getStats() const 
{
    return helmets[mIndex].stats;
}

std::unique_ptr<Pickup> HeadArmor::create() const 
{
    return std::unique_ptr<Pickup>(new HeadArmor(Pickup::getContext(), mIndex, Entity::getHitpoints()));
}
