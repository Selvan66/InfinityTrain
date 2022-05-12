/** @file Interactable.cpp */
#include "Objects/Nodes/Interactable.h"
#include "Objects/Nodes/PlayerNode.h"

Interactable::Interactable(Context& context)
: mDistance(0)
, mIsInteractable(false)
, mTextNode(nullptr)
, mText("")
{
    mCommand.category = Category::Player;
    mCommand.action = derivedAction<PlayerNode>([&] (PlayerNode& player, sf::Time) {
        if (Utility::distance(player, *this) <= mDistance)
            mIsInteractable = true;
        else
            mIsInteractable = false;
    });

    std::unique_ptr<TextNode> node(new TextNode(context));
    mTextNode = node.get();
    SceneNode::attachChild(std::move(node));
}

bool Interactable::IsInteract() const
{
    return mIsInteractable;
}

void Interactable::setDistance(float distance)
{
    mDistance = distance;
}

void Interactable::setText(const std::string& text)
{
    mText = text;
}

void Interactable::setTextPos(const sf::Vector2f& pos)
{
    mTextNode->setPosition(pos);
}

unsigned int Interactable::getCategory() const 
{
    return Category::Interactable;
}

void Interactable::updateCurrent(sf::Time, CommandQueue& commands)
{
    commands.push(mCommand);

    if (mIsInteractable)
    {
        mTextNode->setString(mText);
    }
    else
        mTextNode->setString("");
}
