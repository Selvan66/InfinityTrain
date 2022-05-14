/** @file HeartNode.cpp */
#include "Objects/Nodes/HeartNode.h"
#include "Objects/Nodes/PlayerNode.h"

HeartNode::HeartNode(Context& context, unsigned int value)
: Interactable(context)
, mValue(value)
, mSprite(context.textures.get(TexturesID::Heart))
, mPickedUp(false)
, mIsDestroyed(false)
, mCommand()
{
    Interactable::setDistance(50.f);
    Interactable::setText(std::to_string(value) + "HP");
    Interactable::setTextPos({0, -mSprite.getLocalBounds().height});

    Utility::centerOrigin(mSprite);
    mCommand.category = Category::Player;
    mCommand.action = derivedAction<PlayerNode>([value](PlayerNode& player, sf::Time) {
        player.increaseLive(value);
    });
}

sf::FloatRect HeartNode::getBoundingRect() const 
{
    return sf::Transformable::getTransform().transformRect(mSprite.getGlobalBounds());
}

void HeartNode::interact()
{
    mPickedUp = true;
}

bool HeartNode::isDestroyed() const 
{
    return mIsDestroyed;
}

void HeartNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(mSprite, states);
}

void HeartNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    Interactable::updateCurrent(dt, commands);

    if (mPickedUp && !mIsDestroyed)
    {
        commands.push(mCommand);
        mPickedUp = false;
        mIsDestroyed = true;
    }
}
