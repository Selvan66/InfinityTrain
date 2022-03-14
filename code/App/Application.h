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
	private:
		Context mContext;
		StateStack mStateStack;
};