/** @file Statistics.h */
#pragma once

#include <array>

class Statistics
{
    public:
        typedef unsigned long long int data;

        enum StatsID
        {
            KilledEnemy,
            StartedGames,
            Deads,
            FinishedGames,
            StatisticsCount
        };
    public:
        Statistics();
        void increase(StatsID id);
        data get(StatsID id);
        void save();
        void load();
    private:
        std::array<data, StatisticsCount> mStatistics;
};