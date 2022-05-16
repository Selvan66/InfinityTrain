/** @file HeartNode.h */
#pragma once

#include "Objects/Nodes/Pickup.h"

class HeartNode : public Pickup
{
    public:
        HeartNode(Context& context, int value);
    private:
        int mValue;
};