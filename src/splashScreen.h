#pragma once

#include "menu.h"

namespace Screen
{
	class SplashScreen : public Menu
	{
	private:
		sf::Texture splashScreen;

	public:
		SplashScreen(sf::RenderWindow *window = NULL);
		~SplashScreen();

		int Start() override;
	};
}