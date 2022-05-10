/** @file PlayerNode.cpp */
#include "Objects/Nodes/PlayerNode.h"

#include <iostream> //To delete

PlayerNode::PlayerNode(Context& context)
: Entity(100)
, mContext(context)
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

    mInteractCommand.category = Category::Battlefield;
    mInteractCommand.action = [](SceneNode&, sf::Time) {std::cout << "Interact" << std::endl;};

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

unsigned int PlayerNode::getCategory() const
{
    return Category::Player;
}

sf::FloatRect PlayerNode::getBoundingRect() const
{
    return sf::Transformable::getTransform().transformRect(mSprite.getGlobalBounds());
}

void PlayerNode::remove()
{
    Entity::remove();
}

bool PlayerNode::isMarkedForRemoval() const
{
    return Entity::isDestroyed();
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

    Entity::updateCurrent(dt, commands);
}
