/** @file PlayerInfoGUI.h */

#include <SFML/Graphics.hpp>

#include "Player/PlayerInfo.h"
#include "App/Context.h"

class PlayerInfoGUI : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
    public:
        PlayerInfoGUI(Context& context, PlayerInfo& info);
        void update(sf::Time);
        void setCharacterSize(unsigned int size);
    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void updatePosition();
    private:
        PlayerInfo& mPlayerInfo;
        sf::Text mLiveText;
        sf::Text mMoneyText;
};