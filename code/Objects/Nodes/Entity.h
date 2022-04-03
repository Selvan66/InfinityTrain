/** @file Entity.h */
#pragma once

#include "Objects/Nodes/SceneNode.h"

class Entity : public SceneNode
{
    public:
        explicit Entity(int hitpoints);
        void setVelocity(sf::Vector2f velocity);
        void setVelocity(float vx, float vy);
        void accelerate(sf::Vector2f velocity);
        void accelerate(float vx, float vy);
        sf::Vector2f getVelocity() const;
        int getHitpoints() const;
        void heal(int points);
        void damage(int points);
        void destroy();

        virtual void remove();
        virtual bool isDestroyed() const;
    protected:
        virtual void updateCurrent(sf::Time dt, CommandQueue&);
    private:
        sf::Vector2f mVelocity;
        int mHitpoints;
};