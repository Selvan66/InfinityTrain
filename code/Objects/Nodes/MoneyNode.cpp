/** @file MoneyNode.cpp */
#include "Objects/Nodes/MoneyNode.h"
#include "Objects/Nodes/PlayerNode.h"

MoneyNode::MoneyNode(Context& context, unsigned int value)
: Interactable(context)
, mValue(value)
, mSprite(context.textures.get(TexturesID::Money))
, mPickedUp(false)
, mIsDestroyed(false)
, mCommand()
{
    Interactable::setDistance(50.f);
    Interactable::setText(std::to_string(value) + "$");
    Interactable::setTextPos({0, -mSprite.getLocalBounds().height});

    Utility::centerOrigin(mSprite);
    mCommand.category = Category::Player;
    mCommand.action = derivedAction<PlayerNode>([value](PlayerNode& player, sf::Time) {
        player.increaseMoney(value);
    });
}

sf::FloatRect MoneyNode::getBoundingRect() const 
{
    return sf::Transformable::getTransform().transformRect(mSprite.getGlobalBounds());
}

void MoneyNode::interact()
{
    mPickedUp = true;
}

bool MoneyNode::isDestroyed() const 
{
    return mIsDestroyed;
}

void MoneyNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(mSprite, states);
}

void MoneyNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    Interactable::updateCurrent(dt, commands);

    if (mPickedUp && !mIsDestroyed)
    {
        commands.push(mCommand);
        mPickedUp = false;
        mIsDestroyed = true;
    }
}
