/** @file Pickup.cpp */
#include "Objects/Nodes/Pickup/Pickup.h"
#include "Objects/Nodes/TextNode.h"
#include "Objects/Nodes/PlayerNode.h"

Pickup::Pickup(Context& context, TexturesID texture)
: Interactable()
, mContext(context)
, mSprite(context.textures.get(texture))
, mPickedUp(false)
, mCommand()
, mDescription()
{
    Utility::centerOrigin(mSprite);
}

void Pickup::setCommand(Command command)
{
    mCommand = command;
}

std::string Pickup::getDescription() const
{
    return mDescription;
}

bool Pickup::use(PlayerNode& player)
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

void Pickup::addText(const std::string& text)
{
    std::unique_ptr<TextNode> textNode(new TextNode(mContext));
    textNode->setPosition(0.f, -40.f);
    textNode->setString(text);
    SceneNode::attachChild(std::move(textNode));
}

void Pickup::addDescription(const std::string& description)
{
    mDescription = description;
}

sf::FloatRect Pickup::getBoundingRect() const 
{
    return sf::Transformable::getTransform().transformRect(mSprite.getGlobalBounds());
}

void Pickup::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    Interactable::updateCurrent(dt, commands);

    if (mPickedUp)
        commands.push(mCommand);
}