/** @file Level.h */
#pragma once

#include <array>

#include "Objects/CommandQueue.h"
#include "Objects/Nodes/PlayerNode.h"
#include "Objects/Levels/LvlContext.h"
#include "Objects/Levels/LevelID.h"

class Level : public sf::NonCopyable
{
    public:
        typedef std::unique_ptr<Level> Ptr;
    protected:
        enum Layer
        {
            Background,
            Floor,
            Battlefield,
            LayerCount
        };
    public:
        Level(LvlContext& lvlContext);
        CommandQueue& getCommandQueue();
        void draw();

        virtual void update(sf::Time dt);
        virtual LevelID::ID nextLevel() const;
    protected:
        bool isFinished() const;
        SceneNode* getLayer(Layer layer) const;
        LvlContext& getLvlContext() const;
        void updatePlayer(PlayerNode* player);
    private:
        void buildScene();
        void adaptNodesPosition(SceneNode* node);
        sf::FloatRect getLevelBounds() const;
    private:
        LvlContext& mLvlContext;
        CommandQueue mCommands;
        SceneNode mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayer;
};  