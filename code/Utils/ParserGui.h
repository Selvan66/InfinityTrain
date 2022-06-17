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
        typedef std::unique_ptr<Component> ComponentPtr;
        typedef std::unordered_map<std::string, ComponentPtr> GuiParseType;
        typedef std::unique_ptr<GuiParseType> GuiParsePtr;
    public:
        ParserGui(Context& context);
        bool loadFromFile(const std::string& filename);
        void addConst(const std::string& name, double value);
        GuiParsePtr parse();
    private:
        bool isComponent(const std::string& word) const;
        ComponentPtr getComponent(const std::string& word) const;
        bool isId(const std::string& word) const;
        sf::Vector2f parsePosition(const std::string& value) const;
        void setProperties(ComponentPtr& component, const std::string& propertie, const std::string& value) const;
    private:
        Context& mContext;
        std::stringstream mFile;
        std::unordered_map<std::string, double> mConstants;
};