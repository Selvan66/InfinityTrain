/** @file Settings.h */
#pragma once

#include <string>

#include <nlohmann/json.hpp>

class Settings {
public:
  Settings();
  ~Settings();
  void save();
  void load();
  template <typename T>
  T get(const std::string &id, const std::string &id2 = "") const;

  template <typename T>
  void set(const T &value, const std::string &id, const std::string &id2 = "");

private:
  nlohmann::json mSettings;
};

template <typename T>
T Settings::get(const std::string &id, const std::string &id2) const {
  if (id2 != "")
    return mSettings.at(id).at(id2);
  return mSettings.at(id);
}

template <typename T>
void Settings::set(const T &value, const std::string &id,
                   const std::string &id2) {
  if (id2 != "") {
    mSettings.at(id).at(id2) = value;
    return;
  }
  mSettings.at(id) = value;
}