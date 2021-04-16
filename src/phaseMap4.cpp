#include "phaseMap4.h"

using namespace PhaseMap;

PhaseMap4::PhaseMap4(std::string path) : PhaseMapGeneral(path),
                                        clock(),
                                        elapsed(),
                                        boss({50*TILE_SIZE, 10*TILE_SIZE}, {4.f, 4.f}, 300.f, 15.f),
                                        flyingEnemiesList()
{
}
PhaseMap4::~PhaseMap4()
{
}

void PhaseMap4::update(int &controller)
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

    if (!this->flyingEnemiesList.isEmpty())
        this->flyingEnemiesList.update(this->player1);

    //if (clock.getElapsedTime().asSeconds() > 10)
        this->boss.update(this->player1);

    phaseTransition(controller);
}

void PhaseMap4::render(sf::RenderWindow &window, int &controller)
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

    if (!this->flyingEnemiesList.isEmpty())
        this->flyingEnemiesList.render(window);


    this->boss.render(window);

    phaseMapManager.draw(window);
    window.display();
}

void PhaseMap4::placingEnemies()
{
    this->elapsed = this->clock.getElapsedTime();
    
    if (elapsed.asSeconds() >= 15 && this->flyingEnemiesList.getQuantity() == 0)
    {
        std::cout << elapsed.asSeconds() << std::endl;
        Entidade::Enemy::FlyingEnemy *f1 = new Entidade::Enemy::FlyingEnemy({7 * TILE_SIZE, 18 * TILE_SIZE}, {3, 3}, 50, 15);
        this->flyingEnemiesList.include(f1);
    }
    if (elapsed.asSeconds() >= 25 && this->flyingEnemiesList.getQuantity() == 1)
    {
        std::cout << elapsed.asSeconds() << std::endl;
        Entidade::Enemy::FlyingEnemy *f2 = new Entidade::Enemy::FlyingEnemy({65 * TILE_SIZE, 18 * TILE_SIZE}, {3, 3}, 50, 15);
        this->flyingEnemiesList.include(f2);
    }
}
void PhaseMap4::loadEnemiesListsInCollision()
{
    collisionManager.setBoss(&this->boss);
    collisionManager.setFlyingEnemiesList(&this->flyingEnemiesList);
}


void PhaseMap4::renderPhaseBackGround(sf::RenderWindow &window)
{
}