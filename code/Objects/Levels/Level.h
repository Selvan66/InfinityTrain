/** @file Level.h */
#pragma once

#include <array>

#include "Objects/CommandQueue.h"
#include "Objects/Nodes/SceneNode.h"
#include "App/Context.h"

class Level : public sf::NonCopyable
{
    public:
        typedef std::unique_ptr<Level> Ptr;
    public:
        explicit Level(Context& context);
        sf::FloatRect getLevelBounds() const;
        void update(sf::Time dt);
        void draw();
        bool isFinished() const;
    protected:
        enum Layer
        {
            Background,
            Battlefield,
            LayerCount
        };
    protected:
        Context& getContext() const;
        CommandQueue& getCommandQueue();
        SceneNode* getLayer(Layer layer) const;
    private:
        void handleCollision();
        void buildScene();
    private:
        Context& mContext;
        CommandQueue mCommands;
        sf::FloatRect mLevelBounds;
        SceneNode mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayer;
        bool mFinished;
};  