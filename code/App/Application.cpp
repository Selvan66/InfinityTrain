/** @file Application.cpp */
#include "App/Application.h"
#include "States/MenuState.h"
#include "States/MenuOptionsState.h"
#include "States/SettingState.h"
#include "States/GraphicsSettingState.h"
#include "States/AudioSettingState.h"
#include "States/StatisticsState.h"

Application::Application()
: mContext()
, mStateStack(mContext)
{
	mContext.window.setKeyRepeatEnabled(false);
   	mContext.window.setVerticalSyncEnabled(true);

	loadMenuTexture();
	loadFonts();

   	registerStates();
	mStateStack.pushState(StatesID::MenuState);
}

void Application::run()
{
	sf::Clock clock;
	const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
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
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mContext.window.pollEvent(event)) {
		mStateStack.handleEvent(event);
		if (event.type == sf::Event::Closed)
			mContext.window.close();
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mContext.window.clear();
	mStateStack.draw();
	mContext.window.setView(mContext.window.getDefaultView());
	mContext.window.display();
}

void Application::registerStates()
{
	mStateStack.registerState<MenuState>(StatesID::MenuState);
	mStateStack.registerState<MenuOptionsState>(StatesID::MenuOptionsState);
	mStateStack.registerState<SettingState>(StatesID::SettingState);
	mStateStack.registerState<GraphicsSettingState>(StatesID::GraphicsSettingState);
	mStateStack.registerState<AudioSettingState>(StatesID::AudioSettingState);
	mStateStack.registerState<StatisticsState>(StatesID::StatisticsState);
}

void Application::loadMenuTexture()
{
	mContext.textures.load(TexturesID::TitleScreen, "image/TitleScreen.png");
	mContext.textures.load(TexturesID::ArrowButtons, "image/ArrowButtons.png");
	mContext.textures.load(TexturesID::Checkbox, "image/true.png");
}

void Application::loadFonts()
{
	mContext.fonts.load(FontsID::PixelFont, "fonts/PixelFont.ttf");
}