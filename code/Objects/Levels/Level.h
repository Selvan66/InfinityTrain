/** @file Level.h */
#pragma once

#include <array>

#include "Objects/CommandQueue.h"
#include "Objects/Nodes/Door.h"
#include "Objects/Nodes/PlayerNode.h"
#include "Objects/Levels/LevelID.h"
#include "Player/PlayerInfo.h"
#include "App/Context.h"

class Level : public sf::NonCopyable
{
    public:
        typedef std::unique_ptr<Level> Ptr;
    public:
        explicit Level(Context& context, PlayerInfo& playerInfo, unsigned int numLevel);
        sf::FloatRect getLevelBounds() const;
        CommandQueue& getCommandQueue();
        void update(sf::Time dt);
        void draw();
        bool isFinished() const;
        bool isPlayerGoToNextLevel() const;

        virtual LevelID::ID nextLevel() const;
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
        PlayerNode* getPlayer() const;
        Door* getDoor() const;
        unsigned int getNumLevel() const;
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
        Door* mDoor;
        bool mFinished;
        unsigned int mNumLevel;
};  