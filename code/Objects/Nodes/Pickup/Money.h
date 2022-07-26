/** @file Money.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class Money : public Pickup
{
    public:
        Money(Context& context, unsigned int value);
    private:
        virtual void use(PlayerNode& player) override;
    private:
        unsigned int mValue;
};