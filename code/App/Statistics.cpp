/** @file Statistics.cpp */
#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

#include "App/Statistics.h"

Statistics::Statistics() : mStatistics() { load(); }

Statistics::~Statistics() { save(); }

void Statistics::increase(StatsID id, Statistics::data value) {
  mStatistics[id] += value;
}

Statistics::data Statistics::get(StatsID id) const { return mStatistics[id]; }

void Statistics::save() const {
  std::ofstream o("statistics.json");
  nlohmann::json json;
  json["Statistic"] = mStatistics;
  if (o.is_open())
    o << json;
  else
    std::cerr << "Cannot save statistic" << std::endl;
}

void Statistics::load() {
  std::ifstream i("statistics.json");
  nlohmann::json json;
  if (i.is_open()) {
    i >> json;
    if (json.contains("Statistic"))
      mStatistics =
        json.at("Statistic").get<std::array<data, StatisticsCount>>();
  }
}