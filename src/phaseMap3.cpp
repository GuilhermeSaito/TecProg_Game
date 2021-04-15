#include "phaseMap3.h"

using namespace PhaseMap;

PhaseMap3::PhaseMap3(std::string path) : PhaseMapGeneral(path),
                                        zombiesList(),
                                        goblinMagesList(),
                                        flyingEnemiesList()
{
    // Transforming the image to 1080 x 720
}
PhaseMap3::~PhaseMap3()
{
    this->zombiesList.setNull();
    this->goblinMagesList.setNull();
    this->flyingEnemiesList.setNull();
}

void PhaseMap3::update(int &controller)
{
    placingEnemies();

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

    if (!this->zombiesList.isEmpty())
        this->zombiesList.update(this->player1);

    if (!this->goblinMagesList.isEmpty())
        this->goblinMagesList.update(this->player1);

    if (!this->flyingEnemiesList.isEmpty())
        this->flyingEnemiesList.update(this->player1);

    phaseTransition(controller);
}

void PhaseMap3::render(sf::RenderWindow &window, int &controller)
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

    if (!this->zombiesList.isEmpty())
        this->zombiesList.render(window);

    if (!this->goblinMagesList.isEmpty())
        this->goblinMagesList.render(window);

    if (!this->flyingEnemiesList.isEmpty())
        this->flyingEnemiesList.render(window);
        
    phaseMapManager.draw(window);
    window.display();
}

void PhaseMap3::renderPhaseBackGround(sf::RenderWindow &window)
{
    for (auto *i : phaseBackGroundSprite)
        window.draw(*i);
}

void PhaseMap3::placingEnemies()
{
    if (this->player1->getPosition().x >= 1 * TILE_SIZE && this->zombiesList.getQuantity() == 0)
    {
        Entidade::Enemy::Zombie *z1 = new Entidade::Enemy::Zombie({5 * TILE_SIZE, 27 * TILE_SIZE}, {3, 3}, 50, 15);
        this->zombiesList.include(z1);
    }
    if (this->player1->getPosition().x >= 50 * TILE_SIZE && this->zombiesList.getQuantity() == 1)
    {
        Entidade::Enemy::Zombie *z2 = new Entidade::Enemy::Zombie({70 * TILE_SIZE, 21 * TILE_SIZE}, {3, 3}, 50, 15);
        this->zombiesList.include(z2);
    }

    if (this->player1->getPosition().x >= 1 * TILE_SIZE && this->goblinMagesList.getQuantity() == 0)
    {
        Entidade::Enemy::GoblinMage *g1 = new Entidade::Enemy::GoblinMage({7 * TILE_SIZE, 23 * TILE_SIZE}, {3, 3}, 50, 15);
        this->goblinMagesList.include(g1);
    }
    if (this->player1->getPosition().x >= 60 * TILE_SIZE && this->goblinMagesList.getQuantity() == 1)
    {
        Entidade::Enemy::GoblinMage *g2 = new Entidade::Enemy::GoblinMage({78 * TILE_SIZE, 21 * TILE_SIZE}, {3, 3}, 50, 15);
        this->goblinMagesList.include(g2);
    }

    if (this->player1->getPosition().x >= 1 * TILE_SIZE && this->flyingEnemiesList.getQuantity() == 0)
    {
        Entidade::Enemy::FlyingEnemy *f1 = new Entidade::Enemy::FlyingEnemy({7 * TILE_SIZE, 18 * TILE_SIZE}, {3, 3}, 50, 15);
        this->flyingEnemiesList.include(f1);
    }
    if (this->player1->getPosition().x >= 50 * TILE_SIZE && this->flyingEnemiesList.getQuantity() == 1)
    {
        Entidade::Enemy::FlyingEnemy *f2 = new Entidade::Enemy::FlyingEnemy({65 * TILE_SIZE, 18 * TILE_SIZE}, {3, 3}, 50, 15);
        this->flyingEnemiesList.include(f2);
    }
}
void PhaseMap3::loadEnemiesListsInCollision()
{
    collisionManager.setZombieList(&this->zombiesList);
    collisionManager.setGoblinMageList(&this->goblinMagesList);
    collisionManager.setFlyingEnemiesList(&this->flyingEnemiesList);
}
