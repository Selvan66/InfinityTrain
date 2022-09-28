/** @file Buyable.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class Buyable : public Pickup
{
    public:
        Buyable(Context& context, int price, std::unique_ptr<Pickup> pickup);
    protected:
        virtual sf::FloatRect getBoundingRect() const override;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        int mPrice;
        std::unique_ptr<Pickup> mPickup;
};