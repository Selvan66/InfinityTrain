/** @file CloseWeapon.cpp */
#pragma once

#include "Objects/Nodes/Pickup/Equipment/CloseWeapon.h"
#include "Objects/Nodes/Enemy.h"

static std::array<CloseWeaponParam, CloseWeapon::CloseWeaponCount> closeWeapons = 
{
    {
        { "Knife", 1, 25, TexturesID::HeadArmor /*TODO Change*/, sf::IntRect(0, 0, 32, 32) }
    }
};

CloseWeapon::CloseWeapon(Context& context, size_t index)
: CloseWeapon(context, index, closeWeapons[index].ammos)
{ }

CloseWeapon::CloseWeapon(Context& context, size_t index, int ammos)
: Weapon(context, ammos)
, mIndex(index)
, mAnimation(context.textures.get(closeWeapons[index].animation))
{
    mAnimation.setFrameSize({closeWeapons[index].animationRect.width, closeWeapons[index].animationRect.height});
    mAnimation.setNumFrames(1);
    mAnimation.setDuration(sf::seconds(0.5f));

    Command command;
    command.category = Category::Enemy;
    command.action = derivedAction<Enemy>([&](Enemy& enemy, sf::Time)
    {
        if (enemy.getBoundingRect().intersects(Pickup::getBoundingRect()))
        {
            enemy.damage(closeWeapons[mIndex].damage);
            mAnimation.restart();
        }   
    });

    Pickup::setTexture(closeWeapons[index].animation);
    Pickup::setText(closeWeapons[index].name);
}

sf::FloatRect CloseWeapon::getBoundingRect() const 
{
    return SceneNode::getWorldTransform().transformRect(mAnimation.getGlobalBounds());
}

std::unique_ptr<Pickup> CloseWeapon::create() const 
{
    return std::unique_ptr<Pickup>(new CloseWeapon(Pickup::getContext(), mIndex, Entity::getHitpoints()));   
}

void CloseWeapon::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    Weapon::updateCurrent(dt, commands);
    mAnimation.update(dt);
}
