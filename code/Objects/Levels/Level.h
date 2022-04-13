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
        explicit Level(Context& context, Player& player);
        sf::FloatRect getLevelBounds() const;
        void update(sf::Time dt);
        void draw();
        bool isFinished() const;
    protected:
        Context& getContext() const;
        CommandQueue& getCommandQueue();
        virtual void buildScene();
    private:
        void handleCollision();
    private:
        enum Layer
        {
            Background,
            Battlefield,
            LayerCount
        };
    private:
        Context& mContext;
        Player& mPlayer;
        CommandQueue mCommands;
        sf::FloatRect mLevelBounds;
        SceneNode mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayer;
        bool mFinished;
};  