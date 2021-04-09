#include "phaseMap2.h"

using namespace PhaseMap;

PhaseMap2::PhaseMap2(std::string path) : PhaseMapGeneral(path),
                                         zombiesList(),
                                         goblinMagesList()
{
    // Transforming the image to 1080 x 720
}
PhaseMap2::~PhaseMap2()
{
    for (auto *i : phaseBackGroundSprite)
        delete i;

    if (!this->zombiesList.isEmpty())
    {
        Element<Entidade::Enemy::Zombie> *z = this->zombiesList.getFirst();
        z = z->getNext();
        while (z != NULL)
        {
            Element<Entidade::Enemy::Zombie> *zAux = z->getPrevious();
            delete zAux;
            z = z->getNext();
        }
        delete z;
    }

    if (!this->goblinMagesList.isEmpty())
    {
        Element<Entidade::Enemy::GoblinMage> *g = this->goblinMagesList.getFirst();
        g = g->getNext();
        while (g != NULL)
        {
            Element<Entidade::Enemy::GoblinMage> *gAux = g->getPrevious();
            delete gAux;
            g = g->getNext();
        }
        delete g;
    }

    collisionManager.clearAllLists();

    phaseBackGroundSprite.clear();
}

void PhaseMap2::update(int &controller)
{
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
    phaseTransition(controller);

    if (!this->zombiesList.isEmpty())
        this->zombiesList.update(this->player1->getPosition().x);

    if (!this->goblinMagesList.isEmpty())
        this->goblinMagesList.update(this->player1->getPosition().x);
}

void PhaseMap2::render(sf::RenderWindow &window, int &controller)
{
    setViewInPlayer1(window);

    sf::Event event;
    if (window.pollEvent(event))
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

    window.clear();
    renderPhaseBackGround(window);
    player1->draw(window);
    if (player2 != NULL)
        player2->draw(window);

    //rendering enemies
    if (!this->zombiesList.isEmpty())
        this->zombiesList.render(window);

    if (!this->goblinMagesList.isEmpty())
        this->goblinMagesList.render(window);

    phaseMapManager.draw(window);
    window.display();
}

void PhaseMap2::renderPhaseBackGround(sf::RenderWindow &window)
{
    for (auto *i : phaseBackGroundSprite)
        window.draw(*i);
}

void PhaseMap2::placingEnemies()
{
    Entidade::Enemy::Zombie *z1 = new Entidade::Enemy::Zombie({5 * TILE_SIZE, 27 * TILE_SIZE}, {3, 3}, 50, 15);
    Entidade::Enemy::Zombie *z2 = new Entidade::Enemy::Zombie({32 * TILE_SIZE, 21 * TILE_SIZE}, {3, 3}, 50, 15);
    Entidade::Enemy::GoblinMage *g1 = new Entidade::Enemy::GoblinMage({7 * TILE_SIZE, 23 * TILE_SIZE}, {3, 3}, 50, 15);
    Entidade::Enemy::GoblinMage *g2 = new Entidade::Enemy::GoblinMage({28 * TILE_SIZE, 21 * TILE_SIZE}, {3, 3}, 50, 15);

    this->zombiesList.include(z1);
    this->zombiesList.include(z2);
    this->goblinMagesList.include(g1);
    this->goblinMagesList.include(g2);
}

void PhaseMap2::loadEnemiesListsInCollision()
{
    collisionManager.setZombieList(&this->zombiesList);
    collisionManager.setGoblinMageList(&this->goblinMagesList);
}