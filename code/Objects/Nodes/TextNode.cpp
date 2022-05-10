/** @file TextNode.cpp */
#include "Objects/Nodes/TextNode.h"
#include "Utils/Utility.h"

TextNode::TextNode(Context& context)
: mText()
{
    mText.setFont(context.fonts.get(FontsID::PixelFont));
    mText.setOutlineThickness(1.5f);
    mText.setOutlineColor(sf::Color::Black);
    setString("");
    mText.setCharacterSize(30);
}

void TextNode::setString(const std::string& text)
{
    mText.setString(text);
    Utility::centerOrigin(mText);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mText, states);
}
