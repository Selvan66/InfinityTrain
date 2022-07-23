/** @file Player.cpp */
#include "Player/Player.h"
#include "App/Context.h"
#include "Utils/Utility.h"
#include "Objects/Nodes/PlayerNode.h"

Player::Player(Context& context)
: mContext(context)
{
    initializeActions();
}

void Player::loadPlayerInput()
{
    mKeyBinding.clear();

    mKeyBinding[Utility::toKey(mContext.settings.get<std::string>("Control", "Up"))] = MoveUp;
    mKeyBinding[Utility::toKey(mContext.settings.get<std::string>("Control", "Down"))] = MoveDown;
    mKeyBinding[Utility::toKey(mContext.settings.get<std::string>("Control", "Left"))] = MoveLeft;
    mKeyBinding[Utility::toKey(mContext.settings.get<std::string>("Control", "Right"))] = MoveRight;
    mKeyBinding[Utility::toKey(mContext.settings.get<std::string>("Control", "Fire"))] = Fire;
    mKeyBinding[Utility::toKey(mContext.settings.get<std::string>("Control", "Special"))] = Special;
    mKeyBinding[Utility::toKey(mContext.settings.get<std::string>("Control", "Interact"))] = Interact;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
    if (event.type == sf::Event::KeyPressed)
    {
        auto found = mKeyBinding.find(event.key.code);
        if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
            commands.push(mActionBinding[found->second]);
    }
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
    for (auto& pair : mKeyBinding)
        if (isRealtimeAction(pair.second) && isOutputPressed(pair.first))
            commands.push(mActionBinding[pair.second]);
}

void Player::initializeActions()
{
    mActionBinding[MoveLeft].action =   derivedAction<PlayerNode>([] (PlayerNode& p, sf::Time) { p.makeAction(PlayerNode::MoveLeft); });
    mActionBinding[MoveRight].action =  derivedAction<PlayerNode>([] (PlayerNode& p, sf::Time) { p.makeAction(PlayerNode::MoveRight); });
    mActionBinding[MoveUp].action =     derivedAction<PlayerNode>([] (PlayerNode& p, sf::Time) { p.makeAction(PlayerNode::MoveUp); });
    mActionBinding[MoveDown].action =   derivedAction<PlayerNode>([] (PlayerNode& p, sf::Time) { p.makeAction(PlayerNode::MoveDown); });
    mActionBinding[Fire].action =       derivedAction<PlayerNode>([] (PlayerNode& p, sf::Time) { p.makeAction(PlayerNode::Fire); });  
    mActionBinding[Interact].action =   derivedAction<PlayerNode>([] (PlayerNode& p, sf::Time) { p.makeAction(PlayerNode::Interact); }); 
    mActionBinding[Special].action =    derivedAction<PlayerNode>([] (PlayerNode& p, sf::Time) { p.makeAction(PlayerNode::Special); });  

    for (auto& pair : mActionBinding)
        pair.second.category = Category::Player;
}

bool Player::isOutputPressed(Player::Output key)
{
    sf::Keyboard::Key* keyboard = std::get_if<sf::Keyboard::Key>(&key);
    sf::Mouse::Button* mouse = std::get_if<sf::Mouse::Button>(&key);

    if (keyboard != nullptr)
        return sf::Keyboard::isKeyPressed(*keyboard);
    if (mouse != nullptr)
        return sf::Mouse::isButtonPressed(*mouse);

    return false;
}

bool Player::isRealtimeAction(Action action)
{
    switch (action)
    {
        case MoveUp:
        case MoveDown:
        case MoveLeft:
        case MoveRight:
        case Fire:
        case Special:
        case Interact:
            return true;
            break;   
                 
        default:
            return false;
            break;
    }
}