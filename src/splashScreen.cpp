#include "splashScreen.h"

using namespace Screen;

SplashScreen::SplashScreen(sf::RenderWindow *window) : Menu(window)
{
	if (!splashScreen.loadFromFile("src/data/erase.png"))
		EXIT_FAILURE;
}

SplashScreen::~SplashScreen()
{
	window = NULL;
}

int SplashScreen::Start()
{
	sf::Sprite sprite;
	sprite.setTexture(splashScreen);
	sprite.setScale(sf::Vector2f(1.7, 1.98));

	window->clear();
	window->draw(sprite);
	window->display();

	while (1)
	{
		sf::Event evet;
		if (window->pollEvent(evet))
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