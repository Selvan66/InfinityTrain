/** @file PlayerNode.cpp */
#include "Objects/Nodes/PlayerNode.h"
#include "Objects/Nodes/Interactable.h"

#include <iostream> //To delete

PlayerNode::PlayerNode(Context& context, PlayerInfo& playerInfo)
: Entity(1)
, mContext(context)
, mPlayerInfo(playerInfo)
, mFireCommand()
, mIsFire(false)
, mInteractCommand()
, mIsInteract(false)
, mSpecialCommand()
, mIsSpecial(false)
, mSprite(context.textures.get(TexturesID::Player))
{
    Utility::centerOrigin(mSprite);
    
    mFireCommand.category = Category::Battlefield;
    mFireCommand.action = [](SceneNode&, sf::Time) {std::cout << "Fire" << std::endl;};

    mInteractCommand.category = Category::Interactable;
    mInteractCommand.action = derivedAction<Interactable>([] (Interactable& interactable, sf::Time) {
        if (interactable.IsInteract())
            interactable.interact();
    });
    
    mSpecialCommand.category = Category::Battlefield;
    mSpecialCommand.action = [](SceneNode&, sf::Time) {std::cout << "Special" << std::endl;};
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
    return sf::Transformable::getTransform().transformRect(mSprite.getGlobalBounds());
}

void PlayerNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void PlayerNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    if (mIsFire)
    {
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

    adaptVelocity();
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

void PlayerNode::adaptVelocity()
{
    sf::Vector2f velocity = Entity::getVelocity();

    if (velocity.x != 0.f && velocity.y != 0.f)
        Entity::setVelocity(velocity / std::sqrt(2.f));
}