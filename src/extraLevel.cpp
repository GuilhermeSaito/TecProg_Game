#include "extraLevel.h"

using namespace PhaseMap;

ExtraLevel::ExtraLevel(sf::RenderWindow *window, std::string path) : PhaseMapGeneral(window, path),
                                                                        clock(),
                                                                        elapsed(),
                                                                        threadedBosses(window, {20.f, 2*TILE_SIZE}, {5.f, 5.f}, 300.f, 15.f, 34, this->player1)
{
    if (!lastPhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/deathPhaseBackGround.png"))
        EXIT_FAILURE;
    // Transforming the image to 1080 x 1440
    // Esse aqui vou colocar em dimensoes um pouco diferentes
    for (int i = 0; i < 6; i++)
    {
        sf::Sprite *sprite = new sf::Sprite;
        sprite->setTexture(lastPhaseBackGround);
        sprite->setScale(sf::Vector2f(1, 1));
        sprite->setPosition(sf::Vector2f(1280 * i, 48 * 16));
        phaseBackGroundSprite.push_back(sprite);
    }
}
ExtraLevel::~ExtraLevel()
{
    for (auto *i : phaseBackGroundSprite)
        delete i;
    phaseBackGroundSprite.clear();

    if (!this->enemiesList.isEmpty())
        this->enemiesList.setNull();

    window = NULL;

   // threadedBosses.clear();
}

void ExtraLevel::update(int &controller)
{
    placingEnemies();


    std::cout << "seg antes paused" << std::endl;
    //if (!threadedBosses.empty())
        //for (auto* tb : threadedBosses) tb->setPaused(true); 
        threadedBosses.setPaused(false);
    std::cout << "seg depois paused" << std::endl;

    collisionManager.startVerifyCollision();
    if (isPlayerDead())
    {
        controller = PLAYER_DIE;
        return;
    }


    player1->gravity();
    player1->movementation();
    if (player2 != NULL)
    {
        player2->gravity();
        player2->movementation();
    }
    // Metodo para ir verificando se tem algum inimigo com hp <= 0, se tiver, tira da lista
    enemyKilled();

    //-------------------------------- Esse metodo precisa ser melhorado, ele nao volta ao normal na 4 fase se terminar------------------------
    if (isGameClear() && elapsed.asSeconds() >= 20)
    {
        controller = RANK;
        return;
    }
}

void ExtraLevel::render(int &controller)
{
    // Soh nessa fase que eu nao vou atualizar o view se a posicao do player estiver muito alta
    setViewInPlayer1(controller);

    sf::Event event;
    if (window->pollEvent(event))
        switch (event.type)
        {
        case sf::Event::Closed:
            controller = EXIT_GAME;
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        controller = OPTIONS;
        return;
    }

    window->clear();

    renderPhaseBackGround();
    player1->draw();
    if (player2 != NULL)
        player2->draw();

    if (!this->enemiesList.isEmpty())
        this->enemiesList.render();

    phaseMapManager.draw();
    window->display();

    //for (auto* tb : threadedBosses) tb->render(); 

    std::cout << "seg antes true" << std::endl;
    //if (!threadedBosses.empty())
       // for (auto* tb : threadedBosses) tb->setPaused(true); 
    //threadedBosses.render();
    threadedBosses.setPaused(true);
    std::cout << "seg depois true" << std::endl;
}

void ExtraLevel::renderPhaseBackGround()
{
    for (auto *i : phaseBackGroundSprite)
        window->draw(*i);
}

void ExtraLevel::placingEnemies()
{
    this->elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() > 10)
    {
        threadedBosses.start();
        /*Thread::ThreadedBoss* tb = new Thread::ThreadedBoss(window, {200.f, 18*TILE_SIZE}, {5.f, 5.f}, 300.f, 15.f, 34, this->player1);
        tb->start();
        tb->setPaused(true);
        this->threadedBosses.push_back(tb);
        /*Thread::ThreadedBoss* tb2 = new Thread::ThreadedBoss(window, {600.f, 18*TILE_SIZE}, {5.f, 5.f}, 300.f, 15.f, 34, this->player1);
        tb->start();
        tb->setPaused(true);
        this->threadedBosses.push_back(tb2);*/

        /*this->threadedBosses = new Thread::ThreadedBoss(window, {200.f, 18*TILE_SIZE}, {5.f, 5.f}, 300.f, 15.f, 34, this->player1);
        threadedBosses->start();
        threadedBosses->setPaused(true);
        std::cout << "spawnaram" << std::endl;*/
    }
}
void ExtraLevel::placingObstacles()
{
    // Ainda vou colocar aqui, no update e no render
}

void ExtraLevel::resetClock()
{
    this->clock.restart();
}
