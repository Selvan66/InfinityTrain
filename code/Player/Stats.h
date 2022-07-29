/** @file Stats.h */
#pragma once

#include <array>

#include <SFML/Graphics.hpp>

#include "App/Context.h"
#include "Utils/ParserGui.h"

class Stats : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
    public:
        enum Type
        {
            Lives,
            Money,
            Armor,
            Attack,
            Speed,
            StatsCount
        };
    public:
        explicit Stats(Context& context);
        int getState(Type stat) const;
        bool setStat(Type stat, int value);
        bool updateStat(Type stat, int value);
    protected:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        void updateStatsText();
        void setDefaultStats();
        void setStatWithRange(Type stat, int value);
    private:
        std::array<int, StatsCount> mStats;
        ParserGui::GuiParsePtr mGui;
};