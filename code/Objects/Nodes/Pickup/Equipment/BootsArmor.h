/** @file BootsArmor.h */
#pragma once

#include "Objects/Nodes/Pickup/Equipment/Armor.h"

class BootsArmor : public Armor 
{
    public:
        enum Type
        {
            HeavyBoots,
            LightBoots,
            BootsCount
        };
    public:
        BootsArmor(Context& context, size_t index);
        BootsArmor(Context& context, size_t index, unsigned int durability);
        virtual const std::unordered_map<Stats::Type, int>& getStats() const override;
    protected:
        virtual std::unique_ptr<Pickup> create() const override;
    private:
        size_t mIndex;
};