/** @file Level.h */
#pragma once

#include <array>

#include "Objects/CommandQueue.h"
#include "Objects/Nodes/PlayerNode.h"
#include "Objects/PlayerInfo.h"
#include "App/Context.h"

class Level : public sf::NonCopyable
{
    public:
        typedef std::unique_ptr<Level> Ptr;
    public:
        explicit Level(Context& context, PlayerInfo& playerInfo);
        sf::FloatRect getLevelBounds() const;
        CommandQueue& getCommandQueue();
        void update(sf::Time dt);
        void draw();
        bool isFinished() const;
    protected:
        enum Layer
        {
            Background,
            Floor,
            Battlefield,
            LayerCount
        };
    protected:
        Context& getContext() const;
        SceneNode* getLayer(Layer layer) const;
    private:
        void handleCollision();
        void adaptNodesPosition(SceneNode* node);
        void buildScene();
    private:
        Context& mContext;
        PlayerInfo& mPlayerInfo;
        CommandQueue mCommands;
        sf::FloatRect mLevelBounds;
        SceneNode mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayer;
        PlayerNode* mPlayer;
        bool mFinished;
};  