/** @file SceneNode.h */
#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <set>
#include <cassert>

#include "Utils/Utility.h"
#include "Objects/CommandQueue.h"

class SceneNode : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;
        typedef std::pair<SceneNode*, SceneNode*> Pair;
    public:
        explicit SceneNode(Category category = Category::None);
        void attachChild(Ptr child);
        Ptr detachChild(const SceneNode& node);
        void update(sf::Time dt, CommandQueue& commands);
        sf::Vector2f getWorldPosition() const;
        sf::Transform getWorldTransform() const;
        void onCommand(const Command& command, sf::Time dt);
        void checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPair);
        void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPair);
        void removeObjects();

        virtual Category getCategory() const;
        virtual sf::FloatRect getBoundingRect() const;
        virtual bool isMarkedForRemoval() const;
        virtual bool isDestroyed() const;
    private:
        void updateChildren(sf::Time dt, CommandQueue& commands);
        void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
        void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const; //<Only for debug

        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        std::vector<Ptr> mChildren;
        SceneNode* mParent;
        Category mDefaultCategory;
};