/** @file HeadArmor.h */
#pragma once

#include "Objects/Nodes/Pickup/Equipment/Armor.h"

class HeadArmor : public Armor
{
    public:
        enum Type
        {
            HeavyHelmet,
            HelmetCount
        };
    public:
        HeadArmor(Context& context, size_t index);
        HeadArmor(Context& context, size_t index, int durability);
        virtual const std::unordered_map<Stats::Type, int>& getStats() const override;
    protected:
        virtual std::unique_ptr<Pickup> create() const override;
    private:
        size_t mIndex;
};