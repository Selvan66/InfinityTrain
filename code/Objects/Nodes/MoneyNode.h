/** @file MoneyNode.h */
#pragma once

#include "Objects/Nodes/Pickup.h"

class MoneyNode : public Pickup
{
    public:
        MoneyNode(Context& context, unsigned int value);
    private:
        unsigned int mValue;
};