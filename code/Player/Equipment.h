/** @file Equipment.h */
#pragma once

#include <array>

#include "Player/Pocket.h"

struct PlayerInfo;

class Equipment : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
    public:
        enum Slot
        {
            Head,
            Chest,
            Boots,
            LeftHand,
            RightHand,
            SlotCount
        };
    public:
        Equipment(Context& context, PlayerInfo& playerInfo);
        void equipOrAddToBackpack(std::unique_ptr<Pickup> item);
        void unequip(Slot slot);

        void handleEvent(const sf::Event& event);
        void update();
        void setPosition(sf::Vector2f position);
    protected:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        Context& mContext;
        PlayerInfo& mPlayerInfo;
        sf::Sprite mPlayerSprite;
        std::array<Pocket, SlotCount> mSlots;        
};