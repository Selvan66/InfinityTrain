/** @file Application.cpp */
#include "App/Application.h"

Application::Application()
: mContext(sf::VideoMode(1024, 768))
, mStateStack(mContext)
{
	mContext.window.setKeyRepeatEnabled(false);
   	mContext.window.setVerticalSyncEnabled(true);

   	registerStates();
   
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
}