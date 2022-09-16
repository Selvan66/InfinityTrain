/** @file Level.h */
#pragma once

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
        explicit Level(LvlContext& lvlContext);
        CommandQueue& getCommandQueue();
        void draw();

        virtual void update(sf::Time dt);
        virtual LevelID::ID nextLevel() const;

        static const sf::FloatRect getLevelBounds();
    protected:
        bool isFinished() const;
        SceneNode* getLayer(Layer layer) const;
        LvlContext& getLvlContext() const;
        void updatePlayer(PlayerNode* player);
    private:
        void buildScene();
        void adaptNodesPosition(SceneNode* node);
        void destoryEntitiesOutsideLevel();
    private:
        LvlContext& mLvlContext;
        CommandQueue mCommands;
        SceneNode mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayer;
};  