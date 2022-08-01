/** @file Map.h */
#pragma once
#include <functional>

#include "Objects/Levels/Level.h"

class Map
{
    public:
        explicit Map(Context& context);
        void update(sf::Time dt);
        void handleEvent(const sf::Event& event);
        void draw();
    private:
        template <typename T>
        void registerLevel(LevelID::ID id);
        void registerLevels();
    private:
        Level::Ptr mLevel;
        LvlContext mLvlContext;
        std::array<std::function<Level::Ptr()>, LevelID::LevelCount> mFactories;
        unsigned long long mStartTime;
        ParserGui::GuiParsePtr mGui;
};

template<typename T>
void Map::registerLevel(LevelID::ID id)
{
    mFactories[id] = [this]
    {
        return Level::Ptr(new T(mLvlContext));
    };
}