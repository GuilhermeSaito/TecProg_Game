#include "openMenu.h"

using StartScreen::OpenMenu;

OpenMenu::OpenMenu(sf::RenderWindow *window) : Menu(window)
{
    if (!openMenufont.loadFromFile("src/data/fonts/TurretRoad-Medium.ttf"))
        EXIT_FAILURE;
    if (!openMenuBackGround.loadFromFile("src/data/imageOpenMenu.png"))
        EXIT_FAILURE;

    backGroundSprite.setTexture(openMenuBackGround);
    backGroundSprite.setScale(sf::Vector2f(1.8, 2.4));

    menu1.setFont(openMenufont);
    menu1.setString("New Game");
    menu1.setPosition({500.f, 200.f});
    menu1.setCharacterSize(25);

    menu2.setFont(openMenufont);
    menu2.setString("Continue");
    menu2.setPosition({500.f, 280.f});
    menu2.setCharacterSize(25);

    menu3.setFont(openMenufont);
    menu3.setString("Ranking");
    menu3.setPosition({500.f, 360.f});
    menu3.setCharacterSize(25);

    menu4.setFont(openMenufont);
    menu4.setString("Exit");
    menu4.setPosition({500.f, 420.f});
    menu4.setCharacterSize(25);
}

OpenMenu::~OpenMenu()
{
    window = NULL;
}

int OpenMenu::Start()
{
    int controller = 0;

    // Soh sai desse loop se o jogador escolher sair da aplicacao (pelo x ou altF4) ou se escolher o newGame/Continue/Exit (Ranking tambem, mas voltaria nessa tela depois)
    while (1)
    {
        sf::Event event;
        if (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                return EXIT_GAME;
            if (event.type == sf::Event::KeyPressed)
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    controller--;
                    break;
                case sf::Keyboard::Down:
                    controller++;
                    break;

                // 0 = New Game
                // 1 = Continue
                // 2 = Ranking
                // 3 = Exit
                case sf::Keyboard::Return:
                    if (controller == 0)
                    {
                        // Eh necessario limpar o jSvae, para nao passar lixo para o mainController.
                        if (!jSave.empty())
                            jSave.clear();
                        return PHASE_SELECTION;
                    }
                    else if (controller == 1)
                    {
                        jSave = save.continueRestore();
                        return PHASE_MANAGER;
                    }
                    else if (controller == 2)
                        return RANKING_SCREEN;
                    else
                        return EXIT_GAME;
                }
            if (controller <= 0)
                controller = 0;
            if (controller >= 3)
                controller = 3;
        }
        updateMenuCollor(controller);

        window->clear();
        window->draw(backGroundSprite);
        window->draw(menu1);
        window->draw(menu2);
        window->draw(menu3);
        window->draw(menu4);
        window->display();
    }
}

void OpenMenu::updateMenuCollor(int controller)
{
    if (controller == 0)
    {
        menu1.setFillColor(sf::Color(255, 0, 0, 255));
        menu2.setFillColor(sf::Color(255, 255, 255, 255));
        menu3.setFillColor(sf::Color(255, 255, 255, 255));
        menu4.setFillColor(sf::Color(255, 255, 255, 255));
    }
    else if (controller == 1)
    {
        menu1.setFillColor(sf::Color(255, 255, 255, 255));
        menu2.setFillColor(sf::Color(255, 0, 0, 255));
        menu3.setFillColor(sf::Color(255, 255, 255, 255));
        menu4.setFillColor(sf::Color(255, 255, 255, 255));
    }
    else if (controller == 2)
    {
        menu1.setFillColor(sf::Color(255, 255, 255, 255));
        menu2.setFillColor(sf::Color(255, 255, 255, 255));
        menu3.setFillColor(sf::Color(255, 0, 0, 255));
        menu4.setFillColor(sf::Color(255, 255, 255, 255));
    }
    else
    {
        menu1.setFillColor(sf::Color(255, 255, 255, 255));
        menu2.setFillColor(sf::Color(255, 255, 255, 255));
        menu3.setFillColor(sf::Color(255, 255, 255, 255));
        menu4.setFillColor(sf::Color(255, 0, 0, 255));
    }
}

json OpenMenu::getContinueSave() { return jSave; }