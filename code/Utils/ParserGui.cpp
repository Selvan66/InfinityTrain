/** @file ParserGui.cpp */
#include <fstream>

#include "Utils/ParserGui.h"
#include "Gui/TextButton.h"

ParserGui::ParserGui(Context& context)
: mContext(context)
, mFile()
, mConstants()
{ }

bool ParserGui::loadFromFile(const std::string& filename)
{
    std::fstream file(filename, std::ios_base::in);
    if (!file.is_open())
        return false;
    
    mFile << file.rdbuf();
    
    file.clear();
    return true;
}

void ParserGui::addConst(const std::string& name, double value)
{
    mConstants[name] = value;
}

ParserGui::GuiParsePtr ParserGui::parse()
{
    GuiParsePtr ret(new GuiParseType);
    ComponentPtr component(nullptr);
    std::string word(""), id(""), value("");
    while (!mFile.eof())
    {  
        mFile >> word;
        if (isComponent(word))
        {  
            if (component.get() != nullptr)
            {
                if (id == "")
                    assert(true);   //TODO
                ret->insert(std::make_pair(id, std::move(component)));
                id = "";
            }

            component = getComponent(word);
        }
        else
        {
            mFile >> value;
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

bool ParserGui::isComponent(const std::string& word) const
{
    if ((word[0] == '[') && (word.back() == ']'))
        return true;
    return false;
}

ParserGui::ComponentPtr ParserGui::getComponent(const std::string& word) const
{
    if (word == "[TextButton]")
        return std::move(std::unique_ptr<TextButton>(new TextButton(mContext)));
    else
        assert(true);   //TODO
}

bool ParserGui::isId(const std::string& word) const
{
    if (word == "id")
        return true;
    return false;
}

sf::Vector2f ParserGui::parsePosition(const std::string& value) const
{
    return {500, 500};  //TODO
}

void ParserGui::setProperties(ComponentPtr& component, const std::string& propertie, const std::string& value) const
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
