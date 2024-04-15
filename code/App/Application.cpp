/** @file Application.cpp */
#include "App/Application.h"
#include "States/AboutState.h"
#include "States/AudioSettingState.h"
#include "States/ControlSettingState.h"
#include "States/GameOverState.h"
#include "States/GameState.h"
#include "States/GraphicsSettingState.h"
#include "States/LoadingState.h"
#include "States/MenuOptionsState.h"
#include "States/MenuState.h"
#include "States/PauseState.h"
#include "States/SettingState.h"
#include "States/StatisticsState.h"

Application::Application()
  : mContext(), mStateStack(mContext), mStatisticsText() //< Only for debug
    ,
    mStatisticsUpdateTime() //< Only for
                            // debug
    ,
    mStatisticsNumFrames(0) //< Only for debug
{
  loadMenuTextures();
  loadFonts();
  loadMenuGuiFiles();

  mStatisticsText.setFont(mContext.fonts.get(FontsID::PixelFont)); //< Only for
                                                                   // debug
  mStatisticsText.setPosition(20.f, 20.f); //< Only for debug
  mStatisticsText.setCharacterSize(30u);   //< Only for debug

  registerStates();
  mStateStack.pushState(StatesID::MenuState);
}

void Application::run() {
  sf::Clock clock;
  const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while (mContext.window.isOpen()) {
    sf::Time dt = clock.restart();
    timeSinceLastUpdate += dt;
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;
      processInput();
      update(TimePerFrame);
      if (mStateStack.isEmpty())
        mContext.window.close();
    }

    updateStatistics(dt); //< Only for debug
    render();
  }
}

void Application::processInput() {
  sf::Event event;
  while (mContext.window.pollEvent(event)) {
    mStateStack.handleEvent(event);
    if (event.type == sf::Event::Closed)
      mContext.window.close();
  }
}

void Application::update(sf::Time dt) { mStateStack.update(dt); }

void Application::render() {
  mContext.window.clear();
  mStateStack.draw();
  mContext.window.setView(mContext.window.getDefaultView());
  mContext.window.draw(mStatisticsText); //< Only for debug
  mContext.window.display();
}

void Application::registerStates() {
  mStateStack.registerState<MenuState>(StatesID::MenuState);
  mStateStack.registerState<MenuOptionsState>(StatesID::MenuOptionsState);
  mStateStack.registerState<SettingState>(StatesID::SettingState);
  mStateStack.registerState<GraphicsSettingState>(
    StatesID::GraphicsSettingState);
  mStateStack.registerState<AudioSettingState>(StatesID::AudioSettingState);
  mStateStack.registerState<ControlSettingState>(StatesID::ControlSettingState);
  mStateStack.registerState<StatisticsState>(StatesID::StatisticsState);
  mStateStack.registerState<GameState>(StatesID::GameState);
  mStateStack.registerState<PauseState>(StatesID::PauseState);
  mStateStack.registerState<GameOverState>(StatesID::GameOverState);
  mStateStack.registerState<LoadingState>(StatesID::LoadingState);
  mStateStack.registerState<AboutState>(StatesID::AboutState);
}

void Application::loadMenuTextures() {
  mContext.textures.load(TexturesID::TitleScreen, "image/TitleScreen.png");
  mContext.textures.load(TexturesID::Gui, "image/Gui.png");
  mContext.textures.load(TexturesID::Loading, "image/loading.png");
}

void Application::loadFonts() {
  mContext.fonts.load(FontsID::PixelFont, "fonts/PixelFont.ttf");
}

void Application::loadMenuGuiFiles() {
  mContext.gui.load(GuiFileID::MenuOptions, "gui/MenuOption.gui");
  mContext.gui.load(GuiFileID::GraphicsSetting, "gui/GraphicsSetting.gui");
  mContext.gui.load(GuiFileID::AudioSetting, "gui/AudioSetting.gui");
  mContext.gui.load(GuiFileID::Pause, "gui/Pause.gui");
  mContext.gui.load(GuiFileID::GameOver, "gui/GameOver.gui");
  mContext.gui.load(GuiFileID::Setting, "gui/Setting.gui");
  mContext.gui.load(GuiFileID::Statistics, "gui/Statistics.gui");
  mContext.gui.load(GuiFileID::ControlSetting, "gui/ControlSetting.gui");
  mContext.gui.load(GuiFileID::About, "gui/About.gui");
}

void Application::updateStatistics(sf::Time dt) {
  mStatisticsUpdateTime += dt;
  ++mStatisticsNumFrames;

  if (mStatisticsUpdateTime >= sf::seconds(1.f)) {
    mStatisticsText.setString("FPS: " + std::to_string(mStatisticsNumFrames));

    mStatisticsUpdateTime -= sf::seconds(1.0f);
    mStatisticsNumFrames = 0;
  }
}
