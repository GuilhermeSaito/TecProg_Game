#include "phaseManager.h"

using PhaseMap::PhaseManager;

PhaseManager::PhaseManager(sf::RenderWindow *window) : phaseMap1(window, "src/data/phaseMap/PhaseMapsJson/phaseMap1.json"),
                                                       phaseMap2(window, "src/data/phaseMap/PhaseMapsJson/phaseMap2.json"),
                                                       phaseMap3(window, "src/data/phaseMap/PhaseMapsJson/phaseMap3.json"),
                                                       phaseMap4(window, "src/data/phaseMap/PhaseMapsJson/phaseMap4.json"),
                                                       player1(window, {2 * 48, 27 * 48}, {0, 0}, 1000, 30.0),
                                                       player2(window, {3 * 48, 27 * 48}, {0, 0}, 100, 40.5),
                                                       needToLoadPhase(true),
                                                       controller(EXIT_GAME),
                                                       enemiesList(NULL),
                                                       Menu(window)
{
    if (!openMenufont.loadFromFile("src/data/fonts/TurretRoad-Medium.ttf"))
        EXIT_FAILURE;
}

PhaseManager::~PhaseManager()
{
    window = NULL;
    ResetALL();
}
int PhaseManager::Start(json jContinueSave, const string player1Name, const string player2Name, const bool multiplayer, const int phaseIs)
{
    // Se ele nao estiver vazio, quer dizer que alguem apertou o continuar.
    // Na verdade, posso colocar tudo isso em um metodo, para ficar bonitinho com 1 linha soh aqui, mas estou com preguica no momento...
    if (!jContinueSave.empty())
    {
        if (loadState(jContinueSave) == EXIT_GAME)
            return EXIT_GAME;
    }
    else
    {
        this->player1Name = player1Name;
        this->player2Name = player2Name;
        this->isMultiplayer = multiplayer;
        controller = phaseIs;
        // Esse precisa ficar aqui, para setar os ponteiros do player1 e player2 antes do resetForTransition
        // E precisa ficar depois de saber se eh multiplayer ou nao
        if (loadPhaseMap(this->isMultiplayer) == EXIT_GAME)
            return EXIT_GAME;
        phaseMap1.resetEverythingForTransition();
        phaseMap2.resetEverythingForTransition();
        phaseMap3.resetEverythingForTransition();
        phaseMap4.resetEverythingForTransition();
    }

    // O controller eh para saber em qual fase estah, pois se aperta ESC e vai para save
    // O "phase" vira OPTIONS, mas controller continua como a ultima fase
    // Somente aqui que o controller esta na "frente" do phase, pois estou dando o recover com o controller
    // Daria para passar o save por referencia ou colocar ele como parte da classe
    int phase = controller;
    while (phase >= 0)
    {
        switch (phase)
        {
        case PHASE1:
            controller = phase;
            this->enemiesList = phaseMap1.getEnemiesList();
            phaseMap1.loadListsInCollision();
            phaseMap1.update(phase);
            phaseMap1.render(phase);
            break;
        case PHASE2:
            controller = phase;
            this->enemiesList = phaseMap2.getEnemiesList();
            phaseMap2.loadListsInCollision();
            phaseMap2.update(phase);
            phaseMap2.render(phase);
            break;
        case PHASE3:
            controller = phase;
            this->enemiesList = phaseMap3.getEnemiesList();
            phaseMap3.loadListsInCollision();
            phaseMap3.update(phase);
            phaseMap3.render(phase);
            break;
        case PHASE4:
            controller = phase;
            this->enemiesList = phaseMap4.getEnemiesList();
            phaseMap4.loadListsInCollision();
            phaseMap4.update(phase);
            phaseMap4.render(phase);
            break;

        case PLAYER_DIE:
            normalizeView();
            ResetALL();
            return PLAYER_DIE_SCREEN;

        case OPTIONS:
            showOptions(phase);
            if (phase == EXIT_GAME)
                return EXIT_GAME;
            else if (phase == SAVE)
            {
                saveState();
                ResetALL();
                return OPEN_MENU;
            }
            phase = controller;
            break;

        case RANK:
            save.rankingSave(player1Name, player2Name, player1.getScore(), isMultiplayer);
            normalizeView();
            ResetALL();
            return RANKING_SCREEN;

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

void PhaseManager::normalizeView()
{
    sf::View normalView(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2), sf::Vector2f(1080, 720));
    window->setView(normalView);
}

void PhaseManager::showOptions(int &phase)
{
    normalizeView();

    sf::Text menu1;
    sf::Text menu2;
    sf::Text menu3;

    menu1.setFont(openMenufont);
    menu1.setString("Continue");
    menu1.setPosition({500.f, 200.f});
    menu1.setCharacterSize(25);

    menu2.setFont(openMenufont);
    menu2.setString("Save");
    menu2.setPosition({500.f, 280.f});
    menu2.setCharacterSize(25);

    menu3.setFont(openMenufont);
    menu3.setString("Exit");
    menu3.setPosition({500.f, 360.f});
    menu3.setCharacterSize(25);

    int controller = 0;

    while (1)
    {
        sf::Event event;
        if (window->pollEvent(event))
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

        window->clear();
        window->draw(menu1);
        window->draw(menu2);
        window->draw(menu3);
        window->display();
    }
}

const int PhaseManager::loadState(json j)
{
    int players = 0, players1 = 1, players2 = 2, enemies = j["gamePlaySave"].size() - 1;
    //------------------- Load do Player1 -------------------
    player1.setPosition({j["gamePlaySave"][players1]["players1"]["player1PositionX"], j["gamePlaySave"][players1]["players1"]["player1PositionY"]});
    player1.setHp(j["gamePlaySave"][players1]["players1"]["hp"]);
    player1.setScore(j["gamePlaySave"][players1]["players1"]["score"]);
    //------------------- Load do "Map" -------------------
    this->player1Name = j["gamePlaySave"][players]["players"]["player1Name"].get<string>();
    this->isMultiplayer = j["gamePlaySave"][players]["players"]["multiplayer"];
    controller = j["gamePlaySave"][players]["players"]["phase"];
    //------------------- Load do Player2 -------------------
    if (this->isMultiplayer)
    {
        this->player2Name = j["gamePlaySave"][players]["players"]["player2Name"].get<string>();
        player2.setPosition({j["gamePlaySave"][players2]["players2"]["player2PositionX"], j["gamePlaySave"][players2]["players2"]["player2PositionY"]});
        player2.setHp(j["gamePlaySave"][players2]["players2"]["hp"]);
    }
    //------------------- Load dos Inimigos -------------------
    //  :D e.e :v U.U UwU
    for (auto &j : j["gamePlaySave"][enemies]["enemies"])
    {
        if (j["kind"] == ZOMBIE)
        {
            Entidade::Enemy::Zombie *z = new Entidade::Enemy::Zombie(window, {j["positionX"], j["positionY"]}, {3.f, 3.f}, j["hp"], 15);
            if (controller == PHASE1)
            {
                phaseMap1.getEnemiesList()->include(static_cast<Entidade::EnemyEntity *>(z));
            }
            else if (controller == PHASE2)
            {
                phaseMap2.getEnemiesList()->include(static_cast<Entidade::EnemyEntity *>(z));
            }
            else if (controller == PHASE3)
            {
                phaseMap3.getEnemiesList()->include(static_cast<Entidade::EnemyEntity *>(z));
            }
        }
        else if (j["kind"] == GOBLIN_MAGE)
        {
            Entidade::Enemy::GoblinMage *z = new Entidade::Enemy::GoblinMage(window, {j["positionX"], j["positionY"]}, {3.f, 3.f}, j["hp"], 15);
            if (controller == PHASE2)
            {
                phaseMap2.getEnemiesList()->include(static_cast<Entidade::EnemyEntity *>(z));
            }
            else if (controller == PHASE3)
            {
                phaseMap3.getEnemiesList()->include(static_cast<Entidade::EnemyEntity *>(z));
            }
        }
        else if (j["kind"] == FLYING_ENEMY)
        {
            Entidade::Enemy::FlyingEnemy *z = new Entidade::Enemy::FlyingEnemy(window, {j["positionX"], j["positionY"]}, {3.f, 3.f}, j["hp"], 15);
            if (controller == PHASE3)
            {
                phaseMap3.getEnemiesList()->include(static_cast<Entidade::EnemyEntity *>(z));
            }
            else
            {
                phaseMap4.getEnemiesList()->include(static_cast<Entidade::EnemyEntity *>(z));
            }
        }
        else
        {
            Entidade::Enemy::Boss *z = new Entidade::Enemy::Boss(window, {j["positionX"], j["positionY"]}, {3.f, 3.f}, j["hp"], 30);
            phaseMap4.getEnemiesList()->include(static_cast<Entidade::EnemyEntity *>(z));
        }
    }
    if (loadPhaseMap(this->isMultiplayer) == EXIT_GAME)
        return EXIT_GAME;

    return 1;
}

void PhaseManager::saveState()
{
    // Um metodo do save soh para ter certeza absoluta que nao tera "lixo" dentro dos arrays
    save.clearJson();
    //------------------- Save da "phase" -------------------
    save.setPhasePlayerName(player1Name, player2Name, isMultiplayer, controller);
    //------------------- Save do Player1 -------------------
    save.setPlayer1Save(player1.getSave());
    //------------------- Save dos Inimigos -------------------
    Lists::Element<Entidade::EnemyEntity> *e = this->enemiesList->getFirst();
    while (e != NULL)
    {
        save.setEnemiesSave(e->getInfo()->getSave());
        e = e->getNext();
    }
    // Mesmo se o json do player2 for empty, vai ser tratado na classe save
    //------------------- Save do Player2 -------------------
    save.setPlayer2Save(player2.getSave()); // Eh bom deixar o save do player2 por ultimo, que dai ele ja entra no ultimo espaco do vetor json
    // SE NAO DEIXAR PARA SETAR O PLAYER2 NO FINAL AQUI, VAI DAR ERRO PARA CARREGAR LAH EM CIMA DE RESTAURAR O SAVE!!!
    // Seta todos os saves depois chama essa funcao para colocar tudo no json
    //------------------- Save dos Inimigos -------------------
    save.continueSave();
}

void PhaseManager::ResetALL()
{
    phaseMap1.ResetAll();
    phaseMap2.ResetAll();
    phaseMap3.ResetAll();
    phaseMap4.ResetAll();

    player1.setHp(400);
    player1.setPoints(0);
    player2.setHp(100);

    needToLoadPhase = false;
}