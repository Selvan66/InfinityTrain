/** @file Armor.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class Armor : public Pickup
{
    public:
        Armor(Context& context, int durability);
        virtual bool action(PlayerNode& player) override;
};

struct ArmorParam
{
    const char* name;
    const int durability;
    const std::unordered_map<Stats::Type, int>& stats;
    const TexturesID texture;
    const sf::IntRect textureRect;
};