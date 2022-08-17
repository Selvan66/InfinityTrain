/** @file BootsArmor.cpp */
#include "Objects/Nodes/Pickup/Equipment/BootsArmor.h"
#include "Objects/Nodes/PlayerNode.h"

static std::array<ArmorParam, BootsArmor::BootsCount> boots = 
{
    {
        { "Heavy", 75, { { Stats::Speed, -25 } }, TexturesID::HeavyBoots, sf::IntRect(0, 0, 32, 32) },
        { "Light", 25, { { Stats::Speed, 25 } }, TexturesID::LightBoots, sf::IntRect(0, 0, 32, 32) }
    }
};

BootsArmor::BootsArmor(Context& context, size_t index)
: BootsArmor(context, index, boots[index].durability)
{ }

BootsArmor::BootsArmor(Context& context, size_t index, int durability)
: Armor(context, durability)
, mIndex(index)
{
    Pickup::setTexture(boots[index].texture);
    Pickup::setText(boots[index].name);
}

const std::unordered_map<Stats::Type, int>& BootsArmor::getStats() const 
{
    return boots[mIndex].stats;
}

std::unique_ptr<Pickup> BootsArmor::create() const 
{
    return std::unique_ptr<Pickup>(new BootsArmor(Pickup::getContext(), mIndex, Entity::getHitpoints()));
}