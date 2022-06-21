/** @file ParserGui.cpp */
#include <fstream>
#include <regex>
#include <sstream>

#include "Utils/ParserGui.h"
#include "App/Context.h"
#include "Gui/TextButton.h"

ParserGui::ParserGui()
: mFile()
, mConstants()
{ }

bool ParserGui::loadFromFile(const std::string& filename)
{
    std::fstream file(filename, std::ios_base::in);
    std::stringstream ss;
    if (!file.is_open())
        return false;
    
    mFile.clear();
    ss << file.rdbuf();
    mFile = ss.str();

    file.close();
    return true;
}

void ParserGui::addConst(const std::string& name, float value)
{
    mConstants.add_constant(name, value);
}

ParserGui::GuiParsePtr ParserGui::parse(Context& context)
{
    std::stringstream ss(mFile);
    GuiParsePtr ret(new GuiParseType);
    ComponentPtr component(nullptr);
    std::string word(""), id(""), value("");
    while (!ss.eof())
    {  
        ss >> word;
        if (isComponent(word))
        {  
            if (component.get() != nullptr)
            {
                if (id == "")
                    assert(true);   //TODO
                ret->insert(std::make_pair(id, std::move(component)));
                id = "";
            }

            component = getComponent(word, context);
        }
        else
        {
            ss >> value;
            if (isId(word))
                id = value;
            else
                setProperties(component, word, value);
        }
    }

    if (component.get() != nullptr)
    {
        if (id == "")
            assert(true);   //TODO
        ret->insert(std::make_pair(id, std::move(component)));
    }

    return move(ret);
}

bool ParserGui::isVector(const std::string& word) const
{
    if ((word[0] == '{') && (word.back() != '}'))
        return true;
    return false;
}

std::vector<std::string> ParserGui::splitVector(const std::string& word) const
{
    std::vector<std::string> ret;
    std::stringstream ss(word.substr(1, word.size() - 2));
    std::string item;

    while (std::getline(ss, item, ','))
        ret.push_back(item);

    return ret;
}

bool ParserGui::isComponent(const std::string& word) const
{
    if ((word[0] == '[') && (word.back() == ']'))
        return true;
    return false;
}

ParserGui::ComponentPtr ParserGui::getComponent(const std::string& word, Context& context) const
{
    if (word == "[TextButton]")
        return std::move(std::unique_ptr<TextButton>(new TextButton(context)));
    
    assert(true);   //TODO
}

bool ParserGui::isId(const std::string& word) const
{
    if (word == "id")
        return true;
    return false;
}

sf::Vector2f ParserGui::parsePosition(const std::string& value)
{
    if (!isVector(value))
        assert(true);    //TODO
    
    auto equtaions = splitVector(value);

    float ret[2];
    exprtk::expression<float> expr;
    expr.register_symbol_table(mConstants);
    exprtk::parser<float> parser;

    for (int i = 0; i < equtaions.size(); ++i)
    {
        if (!parser.compile(equtaions[i], expr))
            assert(true);   //TODO
        ret[i] = expr.value();
    }

    return sf::Vector2f(ret[0], ret[1]);
}

void ParserGui::setProperties(ComponentPtr& component, const std::string& propertie, const std::string& value)
{
    if (propertie == "pos")
    {
        component->setPosition(parsePosition(value));
    }
    else if (propertie == "text")
    {
        if (dynamic_cast<TextButton*>(component.get()) == nullptr)
            assert(true);   //TODO
        static_cast<TextButton*>(component.get())->setText(value);
    }
    else
    {
        assert(true);   //TODO
    }
}