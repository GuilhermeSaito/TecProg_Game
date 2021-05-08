#include "splashScreen.h"

using namespace Screen;

SplashScreen::SplashScreen(sf::RenderWindow *window) : Menu(window)
{
	if (!splashScreen.loadFromFile("src/data/backGroundForPhaseAfterPlayerDie/backGround1.jpg"))
		EXIT_FAILURE;
}

SplashScreen::~SplashScreen()
{
	window = NULL;
}

const int SplashScreen::Start()
{
	sf::Sprite sprite;
	sprite.setTexture(splashScreen);
	sprite.setScale(sf::Vector2f(sf::VideoMode::getDesktopMode().width / (float)1920, sf::VideoMode::getDesktopMode().height / (float)1280));
	sprite.setPosition(sf::Vector2f(0, 0));

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