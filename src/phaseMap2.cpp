#include "phaseMap2.h"

using namespace PhaseMap;

PhaseMap2::PhaseMap2(std::string path) : PhaseMapGeneral(path),
                                         zombiesList(),
                                         goblinMagesList()
{
    // Transforming the image to 1080 x 1440
    for (int i = 0; i < 6; i++)
    {
        sf::Sprite *sprite = new sf::Sprite;
        sprite->setTexture(*(Data::getInstance()->getBlueOceanPhaseBackGround()));
        sprite->setScale(sf::Vector2f(0.308571429, 0.731335703));
        sprite->setPosition(sf::Vector2f(1080 * i, 48 * 4));
        phaseBackGroundSprite.push_back(sprite);
    }
}
PhaseMap2::~PhaseMap2()
{
    for (auto *i : phaseBackGroundSprite)
        delete i;
    phaseBackGroundSprite.clear();

    if (!this->zombiesList.isEmpty())
    {
        this->zombiesList.setNull();
    }

    if (!this->goblinMagesList.isEmpty())
    {
        this->goblinMagesList.setNull();
    }

    collisionManager.clearAllLists();
}

void PhaseMap2::update(int &controller)
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
    phaseTransition(controller);

    if (!this->zombiesList.isEmpty())
        this->zombiesList.update(this->player1);

    if (!this->goblinMagesList.isEmpty())
        this->goblinMagesList.update(this->player1);
}

void PhaseMap2::render(sf::RenderWindow &window, int &controller)
{
    setViewInPlayer1(window, controller);

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

//places enemies according to player's position on the level
void PhaseMap2::placingEnemies()
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
}

void PhaseMap2::loadEnemiesListsInCollision()
{
    collisionManager.setZombieList(&this->zombiesList);
    collisionManager.setGoblinMageList(&this->goblinMagesList);
}