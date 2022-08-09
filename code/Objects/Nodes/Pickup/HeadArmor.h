/** @file HeadArmor.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class HeadArmor : public Pickup
{
    public:
        explicit HeadArmor(Context& context);
    
        virtual bool use(PlayerNode& player) override;
    private:
        Context& mContext;
};