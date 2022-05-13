/** @file SpriteNode.h */
#pragma once

#include "Objects/Nodes/SceneNode.h"

class SpriteNode : public SceneNode
{
    public:
        explicit SpriteNode(const sf::Texture& texture);
        SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        sf::Sprite mSprite;
};