#pragma once

#include "SwitchPanel.h"

class SplashScreen : public SwitchPanel
{
public:
	SplashScreen();
	~SplashScreen();

	int Start(sf::RenderWindow& window) override;
};

