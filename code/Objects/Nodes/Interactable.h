/** @file Interactable.h */
#pragma once

#include "Objects/Nodes/TextNode.h"

class Interactable : public SceneNode
{
    public:
        Interactable(Context& context);
        void setDistance(float distance);
        bool IsInteract() const;

        virtual void interact() = 0;
    private:
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
    private:
        float mDistance;
        bool mIsInteractable;
        Command mCommand;
};