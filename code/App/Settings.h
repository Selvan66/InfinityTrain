/** @file Settings.h */
#pragma once

#include <string>

#include <nlohmann/json.hpp>

class Settings
{
    public:
        Settings();
        ~Settings();
        void save();
        void load();
        template<typename T>
        T get(const std::string& id, const std::string& id2 = "");
    private:
        nlohmann::json mSettings;
};

template<typename T>
T Settings::get(const std::string& id, const std::string& id2)
{
    assert(mSettings.contains(id));
    if (id2 != "")
    {
        assert(mSettings[id].contains(id2));
        return mSettings[id][id2];
    }
    return mSettings[id];
}