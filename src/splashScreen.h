#pragma once

#include "menu.h"

class SplashScreen : public Menu
{
private:
	sf::Texture splashScreen;

public:
	SplashScreen(sf::RenderWindow *window = NULL);
	~SplashScreen();

	int Start() override;
};
