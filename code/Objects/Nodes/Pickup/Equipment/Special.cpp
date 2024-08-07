/** @file Special.cpp */
#include "spdlog/spdlog.h"

#include "Objects/Nodes/Pickup/Equipment/Special.h"
#include "Objects/Nodes/PlayerNode.h"
#include "Utils/Utility.h"

static std::array<SpecialParam, Special::SpecialCount> specials = {{
  {"Portal Gun",
   3,
   sf::seconds(1.f),
   {{}},
   TexturesID::Knife,
   sf::IntRect(0, 0, 32, 32),
   Command()},
}};

void initSpecialsActions(Context& context) {
  specials[Special::PortalGun].action.category = Category::Player;
  specials[Special::PortalGun].action.action =
    derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
      spdlog::trace("Special.cpp - initSpecialsActions | PortalGun Command");
      player.setPosition(Utility::getMousePos(context.window));
    });
}

Special::Special(Context& context, Type type)
  : Special(context, type, specials[type].ammos) {}

Special::Special(Context& context, Type type, int ammos)
  : Pickup(context), mType(type), mUse(false),
    mElapsed(specials[type].duration + sf::seconds(1)) {
  initSpecialsActions(context); // TODO: move this to a
                                // better place
  Pickup::setTexture(specials[type].texture);
  Entity::setHitpoints(ammos);
}

void Special::use() {
  spdlog::trace("Special::use");
  mUse = true;
}

unsigned int Special::getCategory() const {
  return Pickup::getCategory() | Category::Special;
}

std::string Special::getName() const { return specials[mType].name; }

std::string Special::getDescription() const {
  std::stringstream ss;
  ss << getName() << '\n';
  ss << "Ammos: "
     << (Entity::getHitpoints() == INF ? "INF"
                                       : std::to_string(Entity::getHitpoints()))
     << '\n';
  ss << "Cooldown: " << specials[mType].duration.asSeconds() << "s";

  for (auto& stat : getStats())
    ss << '\n' << Stats::toString(stat.first) << ": " << stat.second;
  return ss.str();
}

std::unordered_map<Stats::Type, int> Special::getStats() const {
  return specials[mType].stats;
}

std::unique_ptr<Pickup> Special::create() const {
  return std::unique_ptr<Pickup>(
    new Special(Pickup::getContext(), mType, Entity::getHitpoints()));
}

void Special::updateCurrent(sf::Time dt, CommandQueue& commands) {
  Pickup::updateCurrent(dt, commands);
  mElapsed += dt;
  if (mElapsed >= specials[mType].duration) {
    if (mUse) {
      spdlog::trace("Special::updateCurrent | Using special {}", getName());
      mElapsed = sf::Time::Zero;
      commands.push(specials[mType].action);
      if (Entity::getHitpoints() != INF)
        Entity::damage(1);
    }
  }
  mUse = false;
}
