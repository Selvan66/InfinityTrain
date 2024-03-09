/** @file TextNode.cpp */
#include "Objects/Nodes/TextNode.h"
#include "Utils/Utility.h"

TextNode::TextNode(Context &context) : mText(context) {
  mText.setCharacterSize(30);
}

void TextNode::setString(const std::string &text) { mText.setString(text); }

void TextNode::drawCurrent(sf::RenderTarget &target,
                           sf::RenderStates states) const {
  target.draw(mText, states);
}