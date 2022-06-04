/** @file Map.h */
#pragma once
#include <array>
#include <functional>

#include "App/Context.h"
#include "Objects/Levels/LevelID.h"
#include "Objects/Levels/Level.h"
#include "Player/PlayerInfo.h"
#include "Player/Gui/PlayerInfoGUI.h"

class Map
{
    public:
        Map(Context& context);
        CommandQueue& getCommandQueue();
        void update(sf::Time dt);
        void draw();
    private:
        template <typename T>
        void registerLevel(LevelID::ID id);
        void registerLevels();
        void createLevel();
    private:
        Context& mContext;
        Level::Ptr mLevel;
        unsigned int mNumLevel;
        std::array<std::function<Level::Ptr()>, LevelID::LevelCount> mFactories;
        unsigned long long mStartTime;
        sf::Text mTimerText;
        PlayerInfo mPlayerInfo;
        PlayerInfoGUI mPlayerInfoGui;
};

template<typename T>
void Map::registerLevel(LevelID::ID id)
{
    mFactories[id] = [this]
    {
        return Level::Ptr(new T(mContext, mPlayerInfo));
    };
}
