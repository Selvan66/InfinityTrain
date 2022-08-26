/** @file Pickup.cpp */
#include "Objects/Nodes/Pickup/Pickup.h"
#include "Objects/Nodes/TextNode.h"
#include "Objects/Nodes/PlayerNode.h"

Pickup::Pickup(Context& context)
: Interactable()
, mContext(context)
, mSprite()
, mPickedUp(false)
, mCommand()
, mName()
, mStats()
{ }

std::string Pickup::getDescription() const
{
    std::stringstream ss;
    ss << getName();

    for (auto& stat : getStats())
        ss << '\n' << Stats::toString(stat.first) << ": " << stat.second;
    return ss.str();
}

const std::unordered_map<Stats::Type, int>& Pickup::getStats() const
{
    return mStats;
}

bool Pickup::action(PlayerNode& player)
{ 
    return false;
}

void Pickup::interact()
{
    mPickedUp = true;
}

void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(mSprite, states);
}

std::unique_ptr<Pickup> Pickup::create() const
{
    return std::unique_ptr<Pickup>(new Pickup(mContext));
}

void Pickup::setTexture(TexturesID texture)
{
    mSprite.setTexture(mContext.textures.get(texture));
    Utility::centerOrigin(mSprite);
}

void Pickup::setCommand(Command command)
{
    mCommand = command;
}

Context& Pickup::getContext() const
{
    return mContext;
}

const std::string& Pickup::getName() const
{
    return mName;
}

void Pickup::setLabel(const std::string& text)
{
    std::unique_ptr<TextNode> textNode(new TextNode(mContext));
    textNode->setPosition(0.f, -40.f);
    textNode->setString(text);
    SceneNode::attachChild(std::move(textNode));
}

void Pickup::setName(std::string name)
{
    mName = name;
}

sf::FloatRect Pickup::getBoundingRect() const 
{
    return SceneNode::getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void Pickup::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    Interactable::updateCurrent(dt, commands);

    if (mPickedUp) 
    {
        commands.push(mCommand);
        mPickedUp = false;
    }
}