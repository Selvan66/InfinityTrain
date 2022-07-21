/** @file TextNode.h */
#pragma once

#include "Objects/Nodes/SceneNode.h"
#include "App/Context.h"

class TextNode : public SceneNode
{
    public:
        explicit TextNode(Context& context);
        void setString(const std::string& text);
    protected:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        sf::Text mText;
};