#pragma once

#include "menu.h"

class SplashScreen : public Menu
{
public:
	SplashScreen(sf::RenderWindow *window);
	~SplashScreen();

	int Start() override;
};
