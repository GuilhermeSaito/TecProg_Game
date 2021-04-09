#include "phaseMap1.h"

using namespace PhaseMap;

PhaseMap1::PhaseMap1(std::string path) : zombiesList(),
                                         PhaseMapGeneral(path)
{
    // Transforming the image to 1080 x 1440
    for (int i = 0; i < 6; i++)
    {
        sf::Sprite *sprite = new sf::Sprite;
        sprite->setTexture(*(Data::getInstance()->getBeginnerPhaseBackGround()));
        sprite->setScale(sf::Vector2f(0.5625, 1.5));
        sprite->setPosition(sf::Vector2f(1080 * i, 48 * 4));
        phaseBackGroundSprite.push_back(sprite);
    }
}
PhaseMap1::~PhaseMap1()
{
    for (auto *i : phaseBackGroundSprite)
        delete i;

    //deleta todos os zumbis da lista se estiver vazio
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
    this->zombiesList.setNull();

    collisionManager.clearAllLists();

    phaseBackGroundSprite.clear();
}

void PhaseMap1::update(int &controller)
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

    //updates all zombies
    if (!this->zombiesList.isEmpty())
        this->zombiesList.update(player1->getPosition().x);
}

void PhaseMap1::render(sf::RenderWindow &window, int &controller)
{
    setViewInPlayer1(window);

    sf::Event event;
    if (window.pollEvent(event))
        switch (event.type)
        {
        case sf::Event::Closed:
            controller = EXIT_GAME;
            return;
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

    //rendering all zombies
    if (!this->zombiesList.isEmpty())
        zombiesList.render(window);

    phaseMapManager.draw(window);
    window.display();
}

void PhaseMap1::renderPhaseBackGround(sf::RenderWindow &window)
{
    for (auto *i : phaseBackGroundSprite)
        window.draw(*i);
}

void PhaseMap1::placingEnemies()
{
    // For the zombies
    Entidade::Enemy::Zombie *z1 = new Entidade::Enemy::Zombie({5 * TILE_SIZE, 27 * TILE_SIZE}, {5, 5}, 50, 15);
    Entidade::Enemy::Zombie *z2 = new Entidade::Enemy::Zombie({32 * TILE_SIZE, 10 * TILE_SIZE}, {5, 5}, 50, 15);
    Entidade::Enemy::Zombie *z3 = new Entidade::Enemy::Zombie({72 * TILE_SIZE, 10 * TILE_SIZE}, {5, 5}, 50, 15);
    Entidade::Enemy::Zombie *z4 = new Entidade::Enemy::Zombie({120 * TILE_SIZE, 10 * TILE_SIZE}, {5, 5}, 50, 15);

    this->zombiesList.include(z1);
    this->zombiesList.include(z2);
    this->zombiesList.include(z3);
    this->zombiesList.include(z4);
}

void PhaseMap1::loadZombieListInCollision()
{
    collisionManager.setZombieList(&zombiesList);
}

ListElement<Entidade::Enemy::Zombie> *PhaseMap1::getZombiesList()
{
    return &zombiesList;
}