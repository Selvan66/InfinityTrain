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
            LeftHand,
            Head,
            Chest,
            Boots,
            RightHand,
            SlotCount,
            None
        };
    public:
        Equipment(Context& context, PlayerInfo& playerInfo);
        bool canBeEquipped(const std::unique_ptr<Pickup>& item) const;
        void equip(std::unique_ptr<Pickup> item);
        void unequip(Slot slot);
        std::unique_ptr<Pickup>& getItem(Slot slot);
        bool isItem(Slot slot) const;

        void handleEvent(const sf::Event& event);
        void update();
        void setPosition(sf::Vector2f position);
    protected:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        Slot getItemSlot(const std::unique_ptr<Pickup>& item) const;
        void updateArmorStats();
    private:
        Context& mContext;
        PlayerInfo& mPlayerInfo;
        sf::Sprite mPlayerSprite;
        std::array<Pocket, SlotCount> mSlots;        
};