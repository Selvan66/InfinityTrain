/** @file PopupLabel.cpp */
#include <SFML/Window.hpp>

#include "Gui/PopupLabel.h"
#include "Utils/Utility.h"

namespace GUI
{

PopupLabel::PopupLabel(const std::string& text, const FontHolder& fonts)
: mBackground()
, mShow(false)
, mText(text, fonts.get(FontsID::PixelFont), 10)
{
    auto textBounds = mText.getLocalBounds();

    mBackground.setSize(sf::Vector2f(textBounds.width + 20, textBounds.height + 20));
    mBackground.setOutlineThickness(0.5);
    mBackground.setOutlineColor(sf::Color(168, 137, 50));
    mBackground.setFillColor(sf::Color(60, 60, 60));
    auto bounds = mBackground.getLocalBounds();
    mBackground.setOrigin(bounds.left + bounds.width, bounds.top + bounds.height);

    Utility::centerOrigin(mText);
}

void PopupLabel::checkPopup(const sf::FloatRect& objectBounds, const sf::Vector2f& mousePos)
{
    if (objectBounds.contains(mousePos))
    {
        mShow = true;
        setLabelPos(mousePos);
    }
    else
    {
        mShow = false;
    }
}

void PopupLabel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mShow == true)
    {
        target.draw(mBackground);
        target.draw(mText);
    }
}

void PopupLabel::setLabelPos(const sf::Vector2f& pos)
{
    mBackground.setPosition(pos);
    auto& bound = mBackground.getGlobalBounds();
    mText.setPosition(sf::Vector2f(bound.left + bound.width / 2.f, bound.top + bound.height / 2.f));
}

}