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

std::unordered_map<std::string, std::unique_ptr<Component>>&& ParserGui::parse()
{
    std::unordered_map<std::string, std::unique_ptr<Component>> ret;
  
    return move(ret);
}
