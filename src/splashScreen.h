#pragma once

#include "menu.h"

namespace Screen
{
	class SplashScreen : public Menu
	{
	private:
		sf::Texture splashScreen;

		sf::Music music;

	public:
		SplashScreen(sf::RenderWindow *window = NULL);
		~SplashScreen();

		const int Start() override;
	};
}