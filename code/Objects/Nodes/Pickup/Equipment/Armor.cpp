/** @file Armor.cpp */
#include "Objects/Nodes/Pickup/Equipment/Armor.h"
#include "Objects/Nodes/PlayerNode.h"

static const std::array<ArmorParam, Armor::ArmorCount> armors = 
{
    {
        { "Heavy Boots", 75, { { Stats::Speed, -15 } }, TexturesID::HeavyBoots, sf::IntRect(0, 0, 32, 32), Category::Boots },
        { "Light Boots", 25, { { Stats::Speed, 15 } }, TexturesID::LightBoots, sf::IntRect(0, 0, 32, 32), Category::Boots },
        { "Heavy Chest", 150, { { Stats::Speed, -30 } }, TexturesID::ChestArmor, sf::IntRect(0, 0, 32, 32), Category::Chestplate },
        { "Heavy Helmet", 75, { { Stats::Speed, -15 } }, TexturesID::HeadArmor, sf::IntRect(0, 0, 32, 32), Category::Helmet },
    }
};

Armor::Armor(Context& context, Type type)
: Armor(context, type, armors[type].durability) 
{ }

Armor::Armor(Context& context, Type type, int durability)
: Pickup(context)
, mType(type)
{
    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
        player.pickup(create());
        this->destroy();
    });

    Pickup::setCommand(command);
    Pickup::setTexture(armors[type].texture);
    Entity::setHitpoints(durability);
}

unsigned int Armor::getCategory() const 
{
    return Pickup::getCategory() | armors[mType].type;
}

bool Armor::action(PlayerNode& player)
{
    player.pickup(create());
    return true;
}

std::string Armor::getDescription() const 
{
    std::stringstream ss;
    ss << armors[mType].name << '\n';
    ss << "Durability: " << Entity::getHitpoints();

    for (auto& stat : getStats())
        ss << '\n' << Stats::toString(stat.first) << ": " << stat.second;
    return ss.str();
}

std::unordered_map<Stats::Type, int> Armor::getStats() const 
{
    return armors[mType].stats;
}

std::unique_ptr<Pickup> Armor::create() const 
{
    return std::unique_ptr<Pickup>(new Armor(Pickup::getContext(), mType, Entity::getHitpoints())); 
}
