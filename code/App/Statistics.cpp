/** @file Statistics.cpp */
#include <fstream>

#include "spdlog/spdlog.h"
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
  if (!o.is_open()) {
    spdlog::warn("Statistic::save | Cannot save statistics");
    return;
  }

  o << json;
  spdlog::info("Statistic::save | Statistic saved");
}

void Statistics::load() {
  std::ifstream i("statistics.json");
  nlohmann::json json;
  if (!i.is_open()) {
    spdlog::warn("Statistic::load | Cannot load statistics");
    return;
  }

  i >> json;

  if (!json.contains("Statistic")) {
    spdlog::warn("Statistic::load | Statistic file doesn't contain statistics");
    return;
  }

  mStatistics = json.at("Statistic").get<std::array<data, StatisticsCount>>();
  spdlog::info("Statistic::load | Statistic loaded");
}
