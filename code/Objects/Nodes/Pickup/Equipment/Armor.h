/** @file Armor.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class Armor : public Pickup
{
    public:
        Armor(Context& context, int durability);
        virtual bool action(PlayerNode& player) override;
        virtual std::string getDescription() const override;
};

struct ArmorParam
{
    const char* name;
    const int durability;
    std::unordered_map<Stats::Type, int> stats;
    const TexturesID texture;
    const sf::IntRect textureRect;
};