#include "phaseManager.h"

using PhaseMap::PhaseManager;

PhaseManager::PhaseManager() : phaseMap1("src/data/phaseMap/PhaseMapsJson/phaseMap1.json"),
                               phaseMap2("src/data/phaseMap/PhaseMapsJson/phaseMap2.json"),
                               phaseMap3("src/data/phaseMap/PhaseMapsJson/phaseMap3.json"),
                               phaseMap4("src/data/phaseMap/PhaseMapsJson/phaseMap4.json"),
                               player1({2 * 48, 27 * 48}, {0, 0}, 100, 30),
                               player2({3 * 48, 27 * 48}, {0, 0}, 100, 40.5),
                               needToLoadPhase(true)
{
}

PhaseManager::~PhaseManager()
{
    ResetALL();
}
int PhaseManager::Start(sf::RenderWindow &window, json jContinueSave, const string player1Name, const string player2Name, const bool multiplayer, const int phaseIs)
{
    int phase;

    // Se ele nao estiver vazio, quer dizer que alguem apertou o continuar.
    // Na verdade, posso colocar tudo isso em um metodo, para ficar bonitinho com 1 linha soh aqui, mas estou com preguica no momento...
    if (!jContinueSave.empty())
    {
        this->player1Name = jContinueSave["players"]["player1Name"].get<string>();
        player1.setPosition({jContinueSave["players"]["player1PositionX"], jContinueSave["players"]["player1PositionY"]});
        this->isMultiplayer = jContinueSave["players"]["multiplayer"];
        phase = jContinueSave["players"]["phase"];
        if (this->isMultiplayer)
        {
            this->player2Name = jContinueSave["players"]["player2Name"].get<string>();
            player2.setPosition({jContinueSave["players"]["player2PositionX"], jContinueSave["players"]["player2PositionY"]});
        }
        if (loadPhaseMap(this->isMultiplayer) == EXIT_GAME)
            return EXIT_GAME;
        
        // Da um jeito de dar ums save nos inimigos e dar um load aqui
    }
    else
    {
        this->player1Name = player1Name;
        this->player2Name = player2Name;
        this->isMultiplayer = multiplayer;
        phase = phaseIs;
        // Esse precisa ficar aqui, para setar os ponteiros do player1 e player2 antes do resetForTransition
        // E precisa ficar depois de saber se eh multiplayer ou nao
        if (loadPhaseMap(this->isMultiplayer) == EXIT_GAME)
            return EXIT_GAME;
        phaseMap1.resetEverythingForTransition();
        phaseMap2.resetEverythingForTransition();
        phaseMap3.resetEverythingForTransition();
        phaseMap4.resetEverythingForTransition();

        loadEnemiesInLevels();
    }

    int controller = phase;
    while (phase >= 0)
    {
        switch (phase)
        {
        case PHASE1:
            controller = phase;
            phaseMap1.loadZombieListInCollision();
            phaseMap1.update(phase);
            phaseMap1.render(window, phase);
            break;
        case PHASE2:
            controller = phase;
            phaseMap2.loadEnemiesListsInCollision();
            phaseMap2.update(phase);
            phaseMap2.render(window, phase);
            break;
        case PHASE3:
            controller = phase;
            phaseMap3.update(phase);
            phaseMap3.render(window, phase);
            break;
        case PHASE4:
            controller = phase;
            phaseMap4.update(phase);
            phaseMap4.render(window, phase);
            break;

        case PLAYER_DIE:
            return showPlayerDie(window);

        case OPTIONS:
            showOptions(window, phase);
            if (phase == EXIT_GAME)
                return EXIT_GAME;
            else if (phase == SAVE)
            {
                save.continueSave(player1Name, player2Name, multiplayer, controller, player1.getPosition(), player2.getPosition());
                ResetALL();
                return OPEN_MENU;
            }
            phase = controller;
            break;

        default:
            return EXIT_GAME;
        }
    }
    return EXIT_GAME;
}

int PhaseManager::loadPhaseMap(const bool multiplayer)
{
    if (needToLoadPhase)
    {
        if (!phaseMap1.loadPhaseMap())
            return EXIT_GAME;
        if (!phaseMap2.loadPhaseMap())
            return EXIT_GAME;
        if (!phaseMap3.loadPhaseMap())
            return EXIT_GAME;
        if (!phaseMap4.loadPhaseMap())
            return EXIT_GAME;
    }

    phaseMap1.setPlayer1(&player1);
    phaseMap2.setPlayer1(&player1);
    phaseMap3.setPlayer1(&player1);
    phaseMap4.setPlayer1(&player1);
    if (multiplayer)
    {
        phaseMap1.setPlayer2(&player2);
        phaseMap2.setPlayer2(&player2);
        phaseMap3.setPlayer2(&player2);
        phaseMap4.setPlayer2(&player2);
    }

    return 1;
}

void PhaseManager::loadEnemiesInLevels()
{
    phaseMap1.placingEnemies();
    phaseMap2.placingEnemies();
}

int PhaseManager::showPlayerDie(sf::RenderWindow &window)
{
    normalizeView(window);

    ResetALL();

    window.clear();
    sf::Sprite playerDie;
    playerDie.setTexture(*(Data::getInstance()->getPlayerDieBackGroundTexture()));
    playerDie.setPosition(sf::Vector2f(window.getSize().x / 2 - window.getSize().x / 4, window.getSize().y / 2 - window.getSize().y / 4));
    window.draw(playerDie);
    window.display();

    while (true)
    {
        sf::Event event;
        if (window.pollEvent(event))
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

void PhaseManager::normalizeView(sf::RenderWindow &window)
{
    sf::View normalView(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Vector2f(1080, 720));
    window.setView(normalView);
}

void PhaseManager::showOptions(sf::RenderWindow &window, int &phase)
{
    normalizeView(window);

    sf::Text menu1;
    sf::Text menu2;
    sf::Text menu3;

    menu1.setFont(*(Data::getInstance()->getOpenMenufont()));
    menu1.setString("Continue");
    menu1.setPosition({500.f, 200.f});
    menu1.setCharacterSize(25);

    menu2.setFont(*(Data::getInstance()->getOpenMenufont()));
    menu2.setString("Save");
    menu2.setPosition({500.f, 280.f});
    menu2.setCharacterSize(25);

    menu3.setFont(*(Data::getInstance()->getOpenMenufont()));
    menu3.setString("Exit");
    menu3.setPosition({500.f, 360.f});
    menu3.setCharacterSize(25);

    int controller = 0;

    while (1)
    {
        sf::Event event;
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                phase = EXIT_GAME;
                return;
            }
            if (event.type == sf::Event::KeyPressed)
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    controller--;
                    break;
                case sf::Keyboard::Down:
                    controller++;
                    break;

                case sf::Keyboard::Return:
                    if (controller == 1)
                        phase = SAVE;
                    else if (controller == 2)
                        phase = EXIT_GAME;
                    return;
                }
            if (controller <= 0)
                controller = 0;
            if (controller >= 2)
                controller = 2;
        }
        if (controller == 0)
        {
            menu1.setFillColor(sf::Color(255, 0, 0, 255));
            menu2.setFillColor(sf::Color(255, 255, 255, 255));
            menu3.setFillColor(sf::Color(255, 255, 255, 255));
        }
        else if (controller == 1)
        {
            menu1.setFillColor(sf::Color(255, 255, 255, 255));
            menu2.setFillColor(sf::Color(255, 0, 0, 255));
            menu3.setFillColor(sf::Color(255, 255, 255, 255));
        }
        else
        {
            menu1.setFillColor(sf::Color(255, 255, 255, 255));
            menu2.setFillColor(sf::Color(255, 255, 255, 255));
            menu3.setFillColor(sf::Color(255, 0, 0, 255));
        }

        window.clear();
        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);
        window.display();
    }
}

void PhaseManager::ResetALL()
{
    phaseMap1.ResetAll();
    phaseMap2.ResetAll();
    phaseMap3.ResetAll();
    phaseMap4.ResetAll();

    needToLoadPhase = false;
}

int PhaseManager::notImplementedYet(sf::RenderWindow &window)
{
    window.clear();
    sf::Sprite notImplementedYet;
    notImplementedYet.setTexture(*(Data::getInstance()->getNotImplementedYet()));
    notImplementedYet.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    window.draw(notImplementedYet);
    window.display();

    while (true)
    {
        sf::Event event;
        if (window.pollEvent(event))
            switch (event.type)
            {
            case sf::Event::MouseButtonPressed:
            case sf::Event::KeyPressed:
                return OPEN_MENU;
            case sf::Event::Closed:
                return -1;
            }
    }
}