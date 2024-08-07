/** @file StatisticsState.cpp */
#include "spdlog/spdlog.h"

#include "Gui/Text.h"
#include "Gui/TextButton.h"
#include "States/StatisticsState.h"

StatisticsState::StatisticsState(StateStack& stack, Context& context)
  : State(stack, context) {
  State::loadGuiParser(GuiFileID::Statistics);
  applyGuiFunctions();
  spdlog::info("StatisticsState::StatisticsState | Statistics State created");
}

void StatisticsState::applyGuiFunctions() {
  auto& context = State::getContext();
  auto number = context.statistics.get(Statistics::TimePlay) / 1000;
  std::string time = Utility::timeToString(number);

  State::getGuiComponent<Text>("TimePlayVar").setString(time);
  State::getGuiComponent<Text>("StartedGamesVar")
    .setString(
      std::to_string(context.statistics.get(Statistics::StartedGames)));
  State::getGuiComponent<Text>("KilledEnemiesVar")
    .setString(
      std::to_string(context.statistics.get(Statistics::KilledEnemies)));
  State::getGuiComponent<Text>("FinishedGamesVar")
    .setString(
      std::to_string(context.statistics.get(Statistics::FinishedGames)));

  State::getGuiComponent<TextButton>("BackButton").setCallback([&]() {
    spdlog::debug("StatisticsState::applyGuiFunctions | BackButton clicked");
    this->requestStackPop();
    this->requestStackPush(StatesID::MenuOptionsState);
  });
}
