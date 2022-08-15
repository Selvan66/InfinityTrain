/** @file Armor.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class Armor : public Pickup
{
    public:
        Armor(Context& context, unsigned int durability);
        virtual bool use(PlayerNode& player) override;
        virtual std::string getDescription() const override;
};

struct ArmorParam
{
    const char* name;
    const unsigned int durability;
    const std::unordered_map<Stats::Type, int>& stats;
    const TexturesID texture;
    const sf::IntRect textureRect;
};