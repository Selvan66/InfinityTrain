/** @file Stats.h */
#pragma once

#include <array>

#include <SFML/Graphics.hpp>

#include "App/Context.h"
#include "Utils/ParserGui.h"

class Stats : public sf::Drawable,
              public sf::Transformable,
              public sf::NonCopyable {
public:
  enum Type { Lives, Armor, Ammo, Money, Attack, Speed, StatsCount };

public:
  explicit Stats(Context& context);
  int getStat(Type stat) const;
  bool setStat(Type stat, int value);
  bool updateStat(Type stat, int value);
  bool updateStat(const std::unordered_map<Type, int>& stats);
  bool restoreStats(const std::unordered_map<Type, int>& stats);

  static const char* toString(Type type);

protected:
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

private:
  void updateStatsText();
  void setDefaultStats();
  void setStatWithRange(Type stat, int value);

private:
  std::array<int, StatsCount> mStats;
  ParserGui::GuiParsePtr mGui;
};
