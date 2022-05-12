/** @file Interactable.h */
#pragma once

#include "Objects/Nodes/TextNode.h"

class Interactable : public SceneNode
{
    public:
        Interactable(Context& context);
        bool IsInteract() const;
        void setDistance(float distance);
        void setText(const std::string& text);
        void setTextPos(const sf::Vector2f& pos);

        virtual void interact() = 0;
        virtual unsigned int getCategory() const override;
    protected:
        virtual void updateCurrent(sf::Time, CommandQueue& commands);
    private:
        float mDistance;
        bool mIsInteractable;
        Command mCommand;
        std::string mText;
        TextNode* mTextNode;
};