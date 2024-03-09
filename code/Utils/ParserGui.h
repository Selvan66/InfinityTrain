/** @file ParserGui.h */
#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "exprtk.hpp"

#include "Gui/Component.h"

struct Context;
class ParserGui {
public:
  typedef std::unique_ptr<Component>
    ComponentPtr;
  typedef std::unordered_map<
    std::string, ComponentPtr>
    GuiParseType;
  typedef std::unique_ptr<GuiParseType>
    GuiParsePtr;

public:
  ParserGui();
  bool loadFromFile(
    const std::string& filename);
  void addConst(const std::string& name,
                float value);
  GuiParsePtr parse(Context& context);

private:
  bool isVector(
    const std::string& word) const;
  std::vector<std::string> splitVector(
    const std::string& word) const;
  bool isComponent(
    const std::string& word) const;
  ComponentPtr
  getComponent(const std::string& word,
               Context& context) const;
  bool
  isId(const std::string& word) const;
  sf::Vector2f parsePosition(
    const std::string& value);
  void setProperties(
    ComponentPtr& component,
    const std::string& propertie,
    const std::string& value);

private:
  std::string mFile;
  exprtk::symbol_table<float>
    mConstants;
};