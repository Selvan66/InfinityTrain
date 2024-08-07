/** @file ParserGui.cpp */
#include <fstream>
#include <sstream>

#include "spdlog/spdlog.h"

#include "App/Context.h"
#include "Gui/Checkbox.h"
#include "Gui/Text.h"
#include "Gui/TextButton.h"
#include "Gui/TextSlider.h"
#include "Gui/TextureButton.h"
#include "Utils/Exceptions/bad_argument.h"
#include "Utils/Exceptions/bad_function_call.h"
#include "Utils/ParserGui.h"
#include "Utils/Utility.h"

ParserGui::ParserGui() : mFile(), mConstants() {}

bool ParserGui::loadFromFile(const std::string& filename) {
  std::fstream file(filename, std::ios_base::in);
  std::stringstream ss;
  if (!file.is_open()) {
    spdlog::warn("ParserGui::loadFromFile | Cannot load file: {}", filename);
    return false;
  }

  mFile.clear();
  ss << file.rdbuf();
  mFile = ss.str();

  file.close();

  spdlog::debug("ParserGui::loadFromFile | {} - load file successful",
                filename);

  return true;
}

void ParserGui::addConst(const std::string& name, float value) {
  spdlog::debug("ParserGui::addConst | name: {}, value: {}", name, value);
  mConstants.add_constant(name, value);
}

ParserGui::GuiParsePtr ParserGui::parse(Context& context) {
  std::stringstream ss(mFile);
  GuiParsePtr ret(new GuiParseType);
  ComponentPtr component(nullptr);
  std::string word(""), id(""), value("");
  while (!ss.eof()) {
    ss >> word;
    if (isComponent(word)) {
      if (component.get() != nullptr) {
        if (id == "") {
          spdlog::error("ParserGui::parse | {} - no such component", word);
          throw Except::bad_argument()
            .add("Parser Gui")
            .add("No id in component");
        }
        ret->insert(std::make_pair(id, std::move(component)));
        id = "";
      }

      component = getComponent(word, context);
    } else {
      ss.get(); // Delete whitespace
      std::getline(ss, value);
      if (isId(word))
        id = value;
      else
        setProperties(component, word, value);
    }
  }

  if (component.get() != nullptr) {
    if (id == "") {
      spdlog::error("ParserGui::parse | {} - no such id in components", id);
      throw Except::bad_argument()
        .add("Parser Gui : parse()")
        .add("No id in component");
    }
    ret->insert(std::make_pair(id, std::move(component)));
  }

  spdlog::debug("ParserGui::parse | File successful parse");

  return ret;
}

bool ParserGui::isVector(const std::string& word) const {
  if ((word[0] == '{') && (word.back() == '}'))
    return true;
  return false;
}

std::vector<std::string> ParserGui::splitVector(const std::string& word) const {
  std::vector<std::string> ret;
  std::stringstream ss(word.substr(1, word.size() - 2));
  std::string item;

  while (std::getline(ss, item, ','))
    ret.push_back(item);

  return ret;
}

bool ParserGui::isComponent(const std::string& word) const {
  if ((word[0] == '[') && (word.back() == ']'))
    return true;
  return false;
}

ParserGui::ComponentPtr ParserGui::getComponent(const std::string& word,
                                                Context& context) const {
  if (word == "[TextButton]") {
    spdlog::debug("ParserGui::getComponent | Create TextButton");
    return std::unique_ptr<TextButton>(new TextButton(context));
  } else if (word == "[CheckBox]") {
    spdlog::debug("ParserGui::getComponent | Create CheckBox");
    return std::unique_ptr<Checkbox>(new Checkbox(context));
  } else if (word == "[TextureButton]") {
    spdlog::debug("ParserGui::getComponent | Create TextureButton");
    return std::unique_ptr<TextureButton>(new TextureButton(context));
  } else if (word == "[Text]") {
    spdlog::debug("ParserGui::getComponent | Create Text");
    return std::unique_ptr<Text>(new Text(context));
  } else if (word == "[TextSlider]") {
    spdlog::debug("ParserGui::getComponent | Create TextSlider");
    return std::unique_ptr<TextSlider>(new TextSlider(context));
  }

  spdlog::error("ParserGui::getComponent | No such component - {}", word);
  throw Except::bad_argument()
    .add("Parser Gui : getComponent()")
    .add("no such component found");
}

bool ParserGui::isId(const std::string& word) const {
  if (word == "id")
    return true;
  return false;
}

sf::Vector2f ParserGui::parsePosition(const std::string& value) {
  if (!isVector(value)) {
    spdlog::error("ParserGui::parsePosition | String isn't a vector - {}",
                  value);
    throw Except::bad_argument()
      .add("Parser Gui : parserPosition()")
      .add("value is not a vector");
  }

  auto equtaions = splitVector(value);

  std::vector<float> ret;
  exprtk::expression<float> expr;
  expr.register_symbol_table(mConstants);
  exprtk::parser<float> parser;

  for (size_t i = 0; i < equtaions.size(); ++i) {
    if (!parser.compile(equtaions[i], expr)) {
      spdlog::error("ParserGui::parsePosition | exprtk cannot compile");
      throw Except::bad_function_call()
        .add("Parser Gui : "
             "parserPosition()")
        .add("exprtk cannot compile");
    }
    ret.push_back(expr.value());
  }

  assert(ret.size() >= 2);

  return sf::Vector2f(ret[0], ret[1]);
}

void ParserGui::setProperties(ComponentPtr& component,
                              const std::string& propertie,
                              const std::string& value) {
  spdlog::debug("ParserGui::setProperties | propertie - {}, value - {}",
                propertie, value);

  if (propertie == "pos") {
    component->setPosition(parsePosition(value));
  } else if (propertie == "text") {
    Utility::safeCasting<TextButton>(component.get())->setText(value);
  } else if (propertie == "string") {
    Utility::safeCasting<Text>(component.get())->setString(value);
  } else if (propertie == "charSize") {
    Utility::safeCasting<Text>(component.get())
      ->setCharacterSize(static_cast<unsigned int>(std::stoul(value)));
  } else if (propertie == "texts") {
    for (auto& text : splitVector(value))
      Utility::safeCasting<TextSlider>(component.get())->addText(text);
  } else {
    spdlog::error("ParserGui::setProperties | Cannot set properties - {}:{}",
                  propertie, value);
    throw Except::bad_argument()
      .add("Parser Gui : setProperties()")
      .add("no such property");
  }
}
