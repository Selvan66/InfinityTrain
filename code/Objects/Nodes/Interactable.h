/** @file Interactable.h */
#pragma once

#include "Objects/Nodes/TextNode.h"
#include "Objects/Nodes/Entity.h"

class Interactable : public Entity
{
    public:
        Interactable();
        bool IsInteract() const;
        void setDistance(float distance);

        virtual void interact() = 0;
        virtual unsigned int getCategory() const override;
    protected:
        virtual void updateCurrent(sf::Time, CommandQueue& commands) override;
    private:
        float mDistance;
        bool mIsInteractable;
        Command mCommand;
};