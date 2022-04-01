/** @file Application.h */
#pragma once

#include "States/StateStack.h" 

class Application
{
	public:
		Application();
		void run();
	private:
		void processInput();
		void update(sf::Time dt);
		void render();
		void registerStates();
		void loadMenuTexture();
		void loadFonts();

		void updateStatistics(sf::Time dt); //< Only for debug
	private:
		Context mContext;
		StateStack mStateStack;

		sf::Text mStatisticsText;	//< Only for debug
		sf::Time mStatisticsUpdateTime;	//< Only for debug
		std::size_t mStatisticsNumFrames;	//< Only for debug
};