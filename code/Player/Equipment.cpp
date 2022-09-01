/** @file Equipment.cpp */
#include "Player/Equipment.h"
#include "Player/PlayerInfo.h"
#include "Objects/Nodes/Pickup/Equipment/HeadArmor.h"
#include "Objects/Nodes/Pickup/Equipment/ChestArmor.h"
#include "Objects/Nodes/Pickup/Equipment/BootsArmor.h"
#include "Objects/Nodes/Pickup/Equipment/Weapon.h"
#include "Utils/Exceptions/bad_argument.h"

#define V1_POCKET Pocket(context)
#define V5_POCKET V1_POCKET, V1_POCKET, V1_POCKET, V1_POCKET, V1_POCKET

Equipment::Equipment(Context& context, PlayerInfo& playerInfo)
: mContext(context)
, mPlayerInfo(playerInfo)
, mPlayerSprite(context.textures.get(TexturesID::Player), sf::IntRect(0, 0, 80, 61))
, mSlots{V5_POCKET}
{ 
    for (int i = 0; i < SlotCount; ++i)
        mSlots[i].setLeftClickCallback([](){ });

    for (int i = 0; i < SlotCount; ++i)
        mSlots[i].setRightClickCallback([this, i](){ this->unequip(static_cast<Slot>(i)); });

    mSlots[Head].setPosition(0.f,-64.f);
    mSlots[Boots].setPosition(0.f, 64.f);
    mSlots[RightHand].setPosition(64.f, 0.f);
    mSlots[LeftHand].setPosition(-64.f, 0.f);

    Utility::centerOrigin(mPlayerSprite);
    mPlayerSprite.setScale({2.f, 2.f});
    sf::Color playerColor = mPlayerSprite.getColor();
    playerColor.a = 128;
    mPlayerSprite.setColor(playerColor);
}

bool Equipment::canBeEquipped(const std::unique_ptr<Pickup>& item) const
{
    Slot slot = getItemSlot(item);
    if (slot == None || isItem(slot))
        return false;
    return true;
}

void Equipment::equip(std::unique_ptr<Pickup> item)
{
    if (!canBeEquipped(item))
        throw Except::bad_argument().add("Equipment : equip()").add("Item cannot be equipped");

    Slot slot = getItemSlot(item);
    mPlayerInfo.stats.updateStat(item->getStats());
    mSlots[slot].addItem(std::move(item));
}

void Equipment::unequip(Slot slot)
{
    if (isItem(slot))
    {
        mPlayerInfo.stats.restoreStats(getItem(slot)->getStats());
        mPlayerInfo.backpack.addItemToBackpack(std::move(mSlots[slot].dropItem()));
    }
}

std::unique_ptr<Pickup>& Equipment::getItem(Slot slot)
{
    return mSlots[slot].getItem();
}

bool Equipment::isItem(Slot slot) const
{
    return mSlots[slot].isItem();
}

void Equipment::handleEvent(const sf::Event& event)
{
    for (auto& slot : mSlots)
        slot.handleEvent(event);
}

void Equipment::update()
{
    for (auto& slot : mSlots)
        if (slot.isItem() && slot.getItem()->isDestroyed())
        {
            mPlayerInfo.stats.restoreStats(slot.getItem()->getStats());
            slot.dropItem();
        }
        
    for (auto& slot : mSlots)
        slot.update();
    
    updateArmorStats();
    updateWeaponStats();
}

void Equipment::setPosition(sf::Vector2f position)
{
    mPlayerSprite.move(position);
    for (auto& slot : mSlots)
        slot.move(position);
}

void Equipment::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    states.transform *= sf::Transformable::getTransform();
    target.draw(mPlayerSprite, states);
    for (auto& slot : mSlots)
        target.draw(slot, states);
}

Equipment::Slot Equipment::getItemSlot(const std::unique_ptr<Pickup>& item) const
{
    if (dynamic_cast<const HeadArmor*>(item.get()))
        return Head;
    if (dynamic_cast<const ChestArmor*>(item.get()))
        return Chest;
    if (dynamic_cast<const BootsArmor*>(item.get()))
        return Boots;
    if (dynamic_cast<const Weapon*>(item.get()))
        return LeftHand;
    return None;
}

void Equipment::updateArmorStats()
{
    int armor = 0;
    if (isItem(Head))
        armor += getItem(Head)->getHitpoints();
    if (isItem(Chest))
        armor += getItem(Chest)->getHitpoints();
    if (isItem(Boots))
        armor += getItem(Boots)->getHitpoints();
    mPlayerInfo.stats.setStat(Stats::Armor, armor);
}

void Equipment::updateWeaponStats()
{
    if (isItem(LeftHand))
        mPlayerInfo.stats.setStat(Stats::Ammo, getItem(LeftHand)->getHitpoints());
}