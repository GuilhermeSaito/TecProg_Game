#include "playerDieScreen.h"

using namespace Screen;

PlayerDieScreen::PlayerDieScreen(sf::RenderWindow *window) : Menu(window)
{
    if (!playerDieTexture.loadFromFile("src/data/playerDieImageScenario/deathWithEffectPhrase.jpg"))
        EXIT_FAILURE;
}
PlayerDieScreen::~PlayerDieScreen()
{
    window = NULL;
}

int PlayerDieScreen::Start()
{
    window->clear();
    sf::Sprite playerDie;
    playerDie.setTexture(playerDieTexture);
    playerDie.setPosition(sf::Vector2f(window->getSize().x / 2 - window->getSize().x / 4, window->getSize().y / 2 - window->getSize().y / 4));
    window->draw(playerDie);
    window->display();

    while (true)
    {
        sf::Event event;
        if (window->pollEvent(event))
            switch (event.type)
            {
            case sf::Event::MouseButtonPressed:
            case sf::Event::KeyPressed:
                return OPEN_MENU;
            case sf::Event::Closed:
                return EXIT_GAME;
            }
    }
}