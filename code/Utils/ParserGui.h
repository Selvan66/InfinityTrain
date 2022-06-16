/** @file ParserGui.h */
#pragma once

#include <string>
#include <sstream>
#include <unordered_map>
#include <memory>

#include "Gui/Component.h"
#include "App/Context.h"

class ParserGui
{
    public:
        ParserGui(Context& context);
        bool loadFromFile(const std::string& filename);
        void addConst(const std::string& name, double value);
        std::unordered_map<std::string, std::unique_ptr<Component>>&& parse();
    private:
        Context& mContext;
        std::stringstream mFile;
        std::unordered_map<std::string, double> mConstants;
};