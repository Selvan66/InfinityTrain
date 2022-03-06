/** @file Application.cpp */
#include "App/Application.h"

Application::Application()
: mContext(sf::VideoMode(1024, 768))
, mStateStack(mContext)
{
	mContext.mWindow.setKeyRepeatEnabled(false);
   	mContext.mWindow.setVerticalSyncEnabled(true);

   	registerStates();
   
}

void Application::run()
{
	sf::Clock clock;
	const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mContext.mWindow.isOpen()) {
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			processInput();
			update(TimePerFrame);
			if (mStateStack.isEmpty())
			    mContext.mWindow.close();
		}
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mContext.mWindow.pollEvent(event)) {
		mStateStack.handleEvent(event);
		if (event.type == sf::Event::Closed)
			mContext.mWindow.close();
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mContext.mWindow.clear();
	mStateStack.draw();
	mContext.mWindow.setView(mContext.mWindow.getDefaultView());
	mContext.mWindow.display();
}

void Application::registerStates()
{
}