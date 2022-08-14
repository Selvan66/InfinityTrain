/** @file BootsArmor.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class BootsArmor : public Pickup 
{
    public:
        BootsArmor(Context& context, unsigned int durability = 100);

        virtual std::string getDescription() const override;
        virtual std::unordered_map<Stats::Type, int> getStats() const override;
        virtual bool use(PlayerNode& player) override;
    protected:
        virtual std::unique_ptr<Pickup> create() const override;
};