/** @file Heart.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class Heart : public Pickup
{
    public:
        Heart(Context& context, int value);
    private:
        int mValue;
};