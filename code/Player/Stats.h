/** @file Stats.h */
#pragma once

#include <array>

#include <SFML/Graphics.hpp>

#include "App/Context.h"

class Stats : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
    public:
        enum Type
        {
            Lives,
            Money,
            StatsCount
        };
    public:
        Stats();
        int getState(Type stat) const;
        void setStat(Type stat, int value);
        void updateStat(Type stat, int value);
    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        std::array<int, StatsCount> mStats;
};