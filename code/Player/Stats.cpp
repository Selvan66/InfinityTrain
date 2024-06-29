/** @file Stats.cpp */
#include "spdlog/spdlog.h"

#include "Gui/Text.h"
#include "Player/Stats.h"
#include "Utils/Utility.h"

Stats::Stats(Context& context) : mStats() {
  ParserGui& parser = context.gui.get(GuiFileID::Stats);
  parser.addConst("TEXT_HEIGHT", 40.f);
  mGui = parser.parse(context);

  setDefaultStats();
}

int Stats::getStat(Type stat) const { return mStats[stat]; }

bool Stats::setStat(Type stat, int value) {
  if (getStat(stat) == value)
    return false;

  spdlog::trace("Stats::setStat | Set stat {} from {} to {}",
                static_cast<int>(stat), mStats[stat], value);
  auto oldStat = mStats[stat];
  setStatWithRange(stat, value);
  updateStatsText();
  return oldStat != mStats[stat];
}

bool Stats::updateStat(Type stat, int value) {
  spdlog::trace("Stats::updateStat | Update stat {} - {} + {}",
                static_cast<int>(stat), mStats[stat], value);
  auto oldStat = mStats[stat];
  setStat(stat, mStats[stat] + value);
  return oldStat != mStats[stat];
}

bool Stats::updateStat(const std::unordered_map<Type, int>& stats) {
  bool changes = false;
  for (auto& stat : stats)
    changes = updateStat(stat.first, stat.second) ? true : changes;
  return changes;
}

bool Stats::restoreStats(const std::unordered_map<Type, int>& stats) {
  bool changes = false;
  for (auto& stat : stats)
    changes = updateStat(stat.first, -stat.second) ? true : changes;
  return changes;
}

const char* Stats::toString(Type type) {
  switch (type) {
  case Type::Lives:
    return "Lives";
  case Type::Armor:
    return "Armor";
  case Type::Ammo:
    return "Ammo";
  case Type::Money:
    return "Money";
  case Type::Attack:
    return "Attack";
  case Type::Speed:
    return "Speed";
  default:
    return "";
  };
}

void Stats::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform = sf::Transformable::getTransform();
  for (auto& component : *mGui)
    target.draw(*component.second, states);
}

void Stats::updateStatsText() {
  Utility::safeCasting<Text>(mGui->at("Lives").get())
    ->setString("Lives: " + std::to_string(mStats[Lives]));
  Utility::safeCasting<Text>(mGui->at("Armor").get())
    ->setString("Armor: " + std::to_string(mStats[Armor]));
  Utility::safeCasting<Text>(mGui->at("Ammo").get())
    ->setString("Ammo: " +
                (mStats[Ammo] == INF ? "INF" : std::to_string(mStats[Ammo])));
  Utility::safeCasting<Text>(mGui->at("Money").get())
    ->setString("Money: " + std::to_string(mStats[Money]));
  Utility::safeCasting<Text>(mGui->at("Attack").get())
    ->setString("Attack: " + std::to_string(mStats[Attack]));
  Utility::safeCasting<Text>(mGui->at("Speed").get())
    ->setString("Speed: " + std::to_string(mStats[Speed]));
}

void Stats::setDefaultStats() {
  setStat(Lives, 100);
  setStat(Armor, 0);
  setStat(Ammo, 0);
  setStat(Money, 0);
  setStat(Attack, 0);
  setStat(Speed, 75);
}

void Stats::setStatWithRange(Type stat, int value) {
  switch (stat) {
  case Lives:
    mStats[stat] = std::min(100, std::max(value,
                                          0)); // 0 <= stat <= 100
    break;
  case Armor:
  case Ammo:
  case Money:
  case Attack:
    mStats[stat] = std::max(0, value); // stat >= 0
    break;
  case Speed:
    mStats[stat] = std::max(25, value); // stat >= 25
    break;
  default:
    // Do nothing
    break;
  }
}
