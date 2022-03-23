/** @file Statistics.h */
#pragma once

#include <array>

class Statistics
{
    public:
        typedef unsigned long long int data;

        enum StatsID
        {
            KilledEnemies,
            StartedGames,
            FinishedGames,
            TimePlay,   // Save in miliseconds
            StatisticsCount
        };
    public:
        Statistics();
        ~Statistics();
        void increase(StatsID id, data value = 1);
        data get(StatsID id) const;
        void save() const;
        void load();
    private:
        std::array<data, StatisticsCount> mStatistics;
};