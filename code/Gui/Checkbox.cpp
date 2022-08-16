/** @file Checkbox.cpp */
#include "Gui/Checkbox.h"
#include "Utils/Utility.h"

Checkbox::Checkbox(Context& context)
: Button(context)
, mCheck(context.textures.get(TexturesID::Gui), sf::IntRect(181, 0, 50, 50))
, mBox(sf::Vector2f(60, 60))
, mIsSelected(false)
{
    Button::setCallback([this](){this->mIsSelected = !this->mIsSelected;});

    Utility::centerOrigin(mCheck);

    Utility::centerOrigin(mBox);
    mBox.setOutlineColor(sf::Color(0, 0, 0));
    mBox.setOutlineThickness(8);
}

void Checkbox::setSelection(bool isSelect)
{
    mIsSelected = isSelect;
}

bool Checkbox::isSelected() const
{
    return mIsSelected;
}

void Checkbox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= sf::Transformable::getTransform();
    target.draw(mBox, states);
    if (mIsSelected)
        target.draw(mCheck, states);
}

sf::FloatRect Checkbox::getGlobalBounds() const
{
    return sf::Transformable::getTransform().transformRect(mBox.getGlobalBounds());
}