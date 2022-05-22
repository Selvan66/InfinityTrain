/** @file PlayerInfoGUI.cpp */
#include "Gui/Player/PlayerInfoGUI.h"

PlayerInfoGUI::PlayerInfoGUI(Context& context, PlayerInfo& info)
: mPlayerInfo(info)
, mLiveText("", context.fonts.get(FontsID::PixelFont))
, mMoneyText("", context.fonts.get(FontsID::PixelFont))
{
    mLiveText.setFillColor(sf::Color::Red);
    mMoneyText.setFillColor(sf::Color::Yellow);

    update(sf::Time());
    updatePosition();
}

void PlayerInfoGUI::update(sf::Time)
{
    mLiveText.setString("Lives: " + std::to_string(mPlayerInfo.lives) + "HP");
    mMoneyText.setString("Money: " + std::to_string(mPlayerInfo.money) + " $");
}

void PlayerInfoGUI::setCharacterSize(unsigned int size)
{
    mLiveText.setCharacterSize(size);
    mMoneyText.setCharacterSize(size);

    updatePosition();
}

void PlayerInfoGUI::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    states.transform *= sf::Transformable::getTransform();
    target.draw(mLiveText, states);
    target.draw(mMoneyText, states);
}

void PlayerInfoGUI::updatePosition()
{
    auto& bounds = mLiveText.getGlobalBounds();
    mMoneyText.setPosition({0, bounds.height * 1.5f});
}
