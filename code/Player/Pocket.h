/** @file Pocket.h */
#pragma once

#include "Gui/Button.h"
#include "App/Context.h"
#include "Objects/Nodes/Pickup.h"

class Pocket : public Button
{
    public:
        explicit Pocket(Context& context);

        void addItem(std::unique_ptr<Pickup> item);
        std::unique_ptr<Pickup> dropItem();
        bool isItem() const;
    protected: 
        virtual sf::FloatRect getGlobalBounds() const override;
        virtual void changeTexture(Button::Type buttonType) override;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        Context& mContext;
        sf::RectangleShape mBackground;
        std::unique_ptr<Pickup> mItem;
};