/** @file PlayerNode.cpp */
#include "Objects/Nodes/PlayerNode.h"
#include "Objects/Nodes/Interactable.h"
#include "Objects/Levels/Level.h"

#include <iostream> //To delete

PlayerNode::PlayerNode(Context& context, PlayerInfo& playerInfo)
: Entity(playerInfo.stats.getState(Stats::Lives))
, mContext(context)
, mPlayerInfo(playerInfo)
, mFireCommand()
, mIsFire(false)
, mInteractCommand()
, mIsInteract(false)
, mSpecialCommand()
, mIsSpecial(false)
, mAnimation(context.textures.get(TexturesID::Player))
, mWeapon(nullptr)
{   
    mFireCommand.category = Category::Battlefield;
    mFireCommand.action = [&](SceneNode&, sf::Time)
    { 
        if (mWeapon != nullptr)
            mWeapon->use(); 
    };

    mInteractCommand.category = Category::Interactable;
    mInteractCommand.action = derivedAction<Interactable>([] (Interactable& interactable, sf::Time) {
        if (interactable.IsInteract())
            interactable.interact();
    });
    
    mSpecialCommand.category = Category::Battlefield;
    mSpecialCommand.action = [](SceneNode&, sf::Time) {std::cout << "Special" << std::endl;};

    mAnimation.setFrameSize({80, 61});
    mAnimation.setNumFrames(9);
    mAnimation.setDuration(sf::seconds(0.7f));
    mAnimation.setRepeating(true);
}

void PlayerNode::makeAction(Action action)
{
    switch (action)
    {
        case MoveUp:
            Entity::accelerate({0.f, static_cast<float>(-mPlayerInfo.stats.getState(Stats::Speed))});
            break;
        case MoveDown:
            Entity::accelerate({0.f, static_cast<float>(mPlayerInfo.stats.getState(Stats::Speed))});
            break;
        case MoveLeft:
            Entity::accelerate({static_cast<float>(-mPlayerInfo.stats.getState(Stats::Speed)), 0.f});
            break;
        case MoveRight:
            Entity::accelerate({static_cast<float>(mPlayerInfo.stats.getState(Stats::Speed)), 0.f});
            break;
        case Fire:
            fire();
            break;
        case Interact:
            interact();
            break;
        case Special:
            special();
            break;
    }    
}

void PlayerNode::pickup(std::unique_ptr<Pickup> pickup)
{
    if (mPlayerInfo.equipment.canBeEquipped(pickup))
        mPlayerInfo.equipment.equip(std::move(pickup));
    else
        mPlayerInfo.backpack.addItemToBackpack(std::move(pickup));
}

bool PlayerNode::updateStat(Stats::Type stat, int value)
{
    return mPlayerInfo.stats.updateStat(stat, value);
}

unsigned int PlayerNode::getCategory() const
{
    return Category::Player;
}

sf::FloatRect PlayerNode::getBoundingRect() const
{
    return SceneNode::getWorldTransform().transformRect(mAnimation.getGlobalBounds());
}

void PlayerNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mAnimation, states);
}

void PlayerNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    if (mIsFire)
    {
        auto a = sf::Mouse::getPosition(mContext.window);
        sf::Vector2f mousePos = mContext.window.mapPixelToCoords(a); 
        if (Level::getLevelBounds().contains(mousePos))
            commands.push(mFireCommand);
        mIsFire = false;
    }
    if (mIsInteract)
    {
        commands.push(mInteractCommand);
        mIsInteract = false;
    }
    if (mIsSpecial)
    {
        commands.push(mSpecialCommand);
        mIsSpecial = false;
    }

    updateAnimation(dt);
    adaptVelocity();
    updateEquipment();
    updateStats();
    Entity::updateCurrent(dt, commands);
}

void PlayerNode::fire()
{
    mIsFire = true;
}

void PlayerNode::interact()
{
    mIsInteract = true;
}

void PlayerNode::special()
{
    mIsSpecial = true;
}

void PlayerNode::updateAnimation(sf::Time dt)
{
    sf::Vector2f velocity = Entity::getVelocity();
    if (velocity.x == 0.f && velocity.y == 0.f)
    {
        mAnimation.restart();
        mAnimation.update(dt);
        mAnimation.pause();
    }
    else
    {
        if (velocity.x > 0.f)
            sf::Transformable::setScale(1.f, 1.f);
        else
            sf::Transformable::setScale(-1.f, 1.f);
            
        mAnimation.play();
    }

    mAnimation.update(dt);
}

void PlayerNode::adaptVelocity()
{
    sf::Vector2f velocity = Entity::getVelocity();

    if (velocity.x != 0.f && velocity.y != 0.f)
        Entity::setVelocity(velocity / std::sqrt(2.f));
}

void PlayerNode::updateEquipment()
{
    if (mWeapon != nullptr)
    {
        if (mPlayerInfo.equipment.isItem(Equipment::LeftHand))
        {
            mPlayerInfo.equipment.getItem(Equipment::LeftHand)->setHitpoints(mWeapon->getHitpoints());
        }
        else 
        {
            SceneNode::detachChild(*mWeapon);
            mWeapon = nullptr;
        }
    }
    else
    {
        if (mPlayerInfo.equipment.isItem(Equipment::LeftHand))
        {
            auto weapon_ptr = mPlayerInfo.equipment.getItem(Equipment::LeftHand)->create();
            weapon_ptr->setPosition(40.f, 0.f);
            weapon_ptr->setDistance(0.f);
            mWeapon = dynamic_cast<Weapon*>(weapon_ptr.get());
            SceneNode::attachChild(std::move(weapon_ptr));
        }
    }
}

void PlayerNode::updateStats()
{
    auto& stats = mPlayerInfo.stats;
    auto& eq = mPlayerInfo.equipment;

    stats.setStat(Stats::Lives, Entity::getHitpoints());

    int armor = 0;
    if (eq.isItem(Equipment::Head))
        armor += eq.getItem(Equipment::Head)->getHitpoints();
    if (eq.isItem(Equipment::Chest))
        armor += eq.getItem(Equipment::Chest)->getHitpoints();
    if (eq.isItem(Equipment::Boots))
        armor += eq.getItem(Equipment::Boots)->getHitpoints();
    stats.setStat(Stats::Armor, armor);
    
    if (eq.isItem(Equipment::LeftHand))
       stats.setStat(Stats::Ammo, eq.getItem(Equipment::LeftHand)->getHitpoints());
}