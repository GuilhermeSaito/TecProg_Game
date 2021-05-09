#include "playerDieScreen.h"

using namespace Screen;

PlayerDieScreen::PlayerDieScreen(sf::RenderWindow *window) : Menu(window)
{
    if (!playerDieTexture.loadFromFile("src/data/playerDieImageScenario/fairy-with-dying-warrior-wallpaper-1920x1080.jpg"))
        EXIT_FAILURE;
    if (!music.openFromFile("src/data/musicsForBackGround_Games/21 Sweet Memories (Ending Theme).ogg"))
        EXIT_FAILURE;
}
PlayerDieScreen::~PlayerDieScreen()
{
    window = NULL;
}

const int PlayerDieScreen::Start()
{
    music.play();
    window->clear();
    sf::Sprite playerDie;
    playerDie.setTexture(playerDieTexture);
    playerDie.setScale(sf::Vector2f(sf::VideoMode::getDesktopMode().width / (float)1920, sf::VideoMode::getDesktopMode().height / (float)1080));
    playerDie.setPosition(sf::Vector2f(0, 0));
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
                music.pause();
                return OPEN_MENU;
            case sf::Event::Closed:
                music.pause();
                return EXIT_GAME;
            }
    }
}