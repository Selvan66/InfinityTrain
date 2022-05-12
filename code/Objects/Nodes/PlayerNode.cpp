/** @file PlayerNode.cpp */
#include "Objects/Nodes/PlayerNode.h"
#include "Objects/Nodes/Interactable.h"

#include <iostream> //To delete

PlayerNode::PlayerNode(Context& context, PlayerInfo& playerInfo)
: Entity(playerInfo.lives)
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

void PlayerNode::increaseMoney(unsigned int value)
{
    mPlayerInfo.money += value;
}

void PlayerNode::increaseLive(int value)
{
    mPlayerInfo.lives += value;
    Entity::heal(value);
}

unsigned int PlayerNode::getCategory() const
{
    return Category::Player;
}

sf::FloatRect PlayerNode::getBoundingRect() const
{
    return sf::Transformable::getTransform().transformRect(mSprite.getGlobalBounds());
}

void PlayerNode::adaptVelocity()
{
    sf::Vector2f velocity = Entity::getVelocity();

    if (velocity.x != 0.f && velocity.y != 0.f)
        Entity::setVelocity(velocity / std::sqrt(2.f));
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
