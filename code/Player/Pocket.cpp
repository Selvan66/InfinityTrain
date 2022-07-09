/** @file Pocket.cpp */
#include "Player/Pocket.h"
#include "Utils/Utility.h"

Pocket::Pocket(Context& context)
: Button(context)
, mContext(context)
, mBackground({32.f, 32.f})
, mItem(nullptr)
{
    mBackground.setOutlineThickness(1.5f);
    mBackground.setOutlineColor(sf::Color::White);
    mBackground.setFillColor(sf::Color::Transparent);
    Utility::centerOrigin(mBackground);
}

void Pocket::addItem(std::unique_ptr<Pickup> item)
{
    mItem = std::move(item);
}

std::unique_ptr<Pickup> Pocket::dropItem()
{
    std::unique_ptr<Pickup> item = std::move(mItem);
    mItem = nullptr;
    return item;
}

bool Pocket::isItem() const
{
    return mItem != nullptr;
}

sf::FloatRect Pocket::getGlobalBounds() const 
{
    return sf::Transformable::getTransform().transformRect(mBackground.getGlobalBounds());
}

void Pocket::changeTexture(Button::Type buttonType)
{
    switch (buttonType)
    {
        case Normal:
            mBackground.setFillColor(sf::Color::Transparent);
            break;
        case Selected:
            mBackground.setFillColor(sf::Color(255, 255, 255, 50));
            break;
        case Pressed:
            mBackground.setFillColor(sf::Color(255, 255, 255, 100));
            break;
    }
}

void Pocket::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    states.transform *= sf::Transformable::getTransform();
    target.draw(mBackground, states);
    if (isItem())
        mItem->drawCurrent(target, states);
}