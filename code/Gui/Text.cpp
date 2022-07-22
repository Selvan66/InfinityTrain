/** @file Text.cpp */
#include "Gui/Text.h"
#include "Utils/Utility.h"

Text::Text(Context& context)
: Component()
, mText("", context.fonts.get(FontsID::PixelFont), 60)
{ 
    mText.setOutlineThickness(2.f);
    mText.setOutlineColor(sf::Color(0, 0, 0));
}

void Text::setString(const std::string& string)
{
    mText.setString(string);
    Utility::centerOrigin(mText);
}

void Text::setCharacterSize(unsigned int size)
{
    mText.setCharacterSize(size);
}

void Text::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    states.transform *= sf::Transformable::getTransform();
    target.draw(mText, states);
}