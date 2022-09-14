/** @file Weapon.cpp */
#include "Objects/Nodes/Pickup/Equipment/Weapon.h"
#include "Objects/Nodes/PlayerNode.h"
#include "Objects/Nodes/Enemy.h"

static std::array<WeaponParam, Weapon::WeaponCount> weapons = {
    {
        { "Knife", INF, 10, sf::seconds(1.f), TexturesID::Knife, sf::IntRect(0, 0, 32, 32), 1, Projectile::None, {52.f, 52.f} },
        { "Sword", 25, 25, sf::seconds(0.3f), TexturesID::Sword, sf::IntRect(0, 0, 160, 32), 5, Projectile::None, {64.f, 64.f} },
        //{ "Bow", 10, 1, sf::seconds(0.5f), TexturesID::Bow, sf::IntRect(0, 0, 32, 32), 4, Projectile::Arrow }
    }
};

Weapon::Weapon(Context& context, size_t index)
: Weapon(context, index, weapons[index].ammos)
{ }

Weapon::Weapon(Context& context, size_t index, int ammos)
: Pickup(context)
, mAttackCommand()
, mUse(false)
, mIndex(index)
, mElapsed()
, mAnimation(context.textures.get(weapons[index].animation))
{
    mAnimation.setFrameSize({32, 32});
    mAnimation.setNumFrames(weapons[index].frameNum);
    mAnimation.setDuration(weapons[index].duration);
    mAnimation.pause();

    mAttackCommand.category = Category::Enemy;
    
    if (weapons[index].projectile == Projectile::None)
    {
        mAttackCommand.action = derivedAction<Enemy>([&](Enemy& enemy, sf::Time dt)
        {
            if (Utility::collision(*this, enemy))
                enemy.damage(weapons[mIndex].damage);
        });
    }
    // TODO : Projectile command

    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
        player.pickup(create());
        this->destroy();
    });
    Pickup::setCommand(command);
    Entity::setHitpoints(ammos);
}

void Weapon::use()
{
    mUse = true;
}

sf::Vector2f Weapon::getSize() const
{
    return weapons[mIndex].size;
}

bool Weapon::action(PlayerNode& player)
{
    player.pickup(create());
    return true;
}

std::string Weapon::getDescription() const 
{
    std::stringstream ss;
    ss << weapons[mIndex].name << '\n';
    ss << "Ammos: " << (Entity::getHitpoints() == INF ? "INF" : std::to_string(Entity::getHitpoints()));
    return ss.str();
}

std::unordered_map<Stats::Type, int> Weapon::getStats() const 
{
    return { { Stats::Attack, weapons[mIndex].damage } };
}

std::unique_ptr<Pickup> Weapon::create() const 
{
    return std::unique_ptr<Pickup>(new Weapon(Pickup::getContext(), mIndex, Entity::getHitpoints()));   
}

sf::FloatRect Weapon::getBoundingRect() const 
{
    return SceneNode::getWorldTransform().transformRect(mAnimation.getGlobalBounds());
}

void Weapon::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    Pickup::updateCurrent(dt, commands);
    mElapsed += dt;
    if (mElapsed >= weapons[mIndex].duration)
    {
        if (mUse)
        {
            commands.push(mAttackCommand);
            mElapsed = sf::Time::Zero;
            mAnimation.play();
            if (Entity::getHitpoints() != INF)
                Entity::damage(1);
        }
    }
    mUse = false;

    mAnimation.update(dt);
    if (mAnimation.isFinished())
    {
        mAnimation.restart();
        mAnimation.update(dt);   
        mAnimation.pause();
    }
}

void Weapon::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(mAnimation, states);
}