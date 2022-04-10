/** @file Level.h */
#pragma once

#include <array>

#include "Objects/CommandQueue.h"
#include "Objects/Nodes/SceneNode.h"
#include "App/Context.h"

class Level : public sf::NonCopyable
{
    public:
        explicit Level(Context& context);
        sf::FloatRect getLevelBounds() const;
        void update(sf::Time dt, CommandQueue& commands);
        void draw();
    protected:
        Context& getContext() const;
        virtual void buildScene();
    private:
        enum Layer
        {
            Background,
            Battlefield,
            LayerCount
        };
    private:
        Context& mContext;
        sf::FloatRect mLevelBounds;
        SceneNode mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayer;
};  