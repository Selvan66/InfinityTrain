/** @file TextNode.h */
#pragma once

#include "Objects/Nodes/SceneNode.h"
#include "App/Context.h"

class TextNode : public SceneNode
{
    public:
        TextNode(Context& context);
        void setString(const std::string& text);
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        sf::Text mText;
};