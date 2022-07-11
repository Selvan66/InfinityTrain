/** @file Map.h */
#pragma once
#include <array>
#include <functional>

#include "App/Context.h"
#include "Objects/Levels/LevelID.h"
#include "Objects/Levels/Level.h"
#include "Player/PlayerInfo.h"
#include "Utils/ParserGui.h"

class Map
{
    public:
        Map(Context& context);
        void update(sf::Time dt);
        void handleEvent(const sf::Event& event);
        void draw();
    private:
        template <typename T>
        void registerLevel(LevelID::ID id);
        void registerLevels();
    private:
        Context& mContext;
        Level::Ptr mLevel;
        unsigned int mNumLevel;
        std::array<std::function<Level::Ptr()>, LevelID::LevelCount> mFactories;
        unsigned long long mStartTime;
        ParserGui::GuiParsePtr mGui;
        PlayerInfo mPlayerInfo;
};

template<typename T>
void Map::registerLevel(LevelID::ID id)
{
    mFactories[id] = [this]
    {
        return Level::Ptr(new T(mContext, mPlayerInfo, mNumLevel));
    };
}
