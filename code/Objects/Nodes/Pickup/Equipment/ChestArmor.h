/** @file ChestArmor.h */
#pragma once

#include "Objects/Nodes/Pickup/Equipment/Armor.h"

class ChestArmor : public Armor 
{
    public:
        enum Type
        {
            HeavyChest,
            ChestCount
        };
    public:
        ChestArmor(Context& context, size_t index);
        ChestArmor(Context& context, size_t index, int durability);
        virtual std::unordered_map<Stats::Type, int> getStats() const override;
    protected:
        virtual std::unique_ptr<Pickup> create() const override;
    private:
        size_t mIndex;
};