#include "playerDieScreen.h"

using namespace Screen;

PlayerDieScreen::PlayerDieScreen(sf::RenderWindow *window) : Menu(window)
{
    if (!playerDieTexture.loadFromFile("src/data/playerDieImageScenario/fairy-with-dying-warrior-wallpaper-1920x1080.jpg"))
        EXIT_FAILURE;
}
PlayerDieScreen::~PlayerDieScreen()
{
    window = NULL;
}

const int PlayerDieScreen::Start()
{
    window->clear();
    sf::Sprite playerDie;
    playerDie.setTexture(playerDieTexture);
    playerDie.setScale({0.35, 0.35});
    playerDie.setPosition(sf::Vector2f(window->getSize().x / 3, window->getSize().y / 3));
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