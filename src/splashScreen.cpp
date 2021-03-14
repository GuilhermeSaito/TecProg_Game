#include "splashScreen.h"
#include "data.h"

SplashScreen::SplashScreen()
{
}

SplashScreen::~SplashScreen()
{
}

int SplashScreen::Start(sf::RenderWindow& window)
{
	sf::Sprite sprite;
	sprite.setTexture(*(Data::getInstance()->getSplashScreenTexture()));
	sprite.setScale(sf::Vector2f(1.7, 1.98));

	window.clear();
	window.draw(sprite);
	window.display();

	while (1)
	{
		sf::Event evet;
		if (window.pollEvent(evet))
			switch (evet.type)
			{
			case sf::Event::MouseButtonPressed:
			case sf::Event::KeyPressed:
				return OPEN_MENU;
			case sf::Event::Closed:
				return EXIT_GAME;
			}
	}
}