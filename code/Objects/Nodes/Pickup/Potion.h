/** @file Potion.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class PlayerNode;

class Potion : public Pickup
{
    public:
        Potion(Context& context, unsigned int value);

        virtual std::string getDescription() const;
        virtual bool use(PlayerNode& player) override;
    private:
        unsigned int mValue;
        std::string mDescription;
};