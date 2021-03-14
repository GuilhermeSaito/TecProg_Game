#include "phaseMap1.h"

using namespace PhaseMap;

PhaseMap1::PhaseMap1(std::string path) :
    PhaseMapGeneral(path)
{
    // Transforming the image to 1080 x 1440
    for (int i = 0; i < 6; i++)
    {
        sf::Sprite* sprite = new sf::Sprite;
        sprite->setTexture(*(Data::getInstance()->getBeginnerPhaseBackGround()));
        sprite->setScale(sf::Vector2f(0.5625, 1.5));
        sprite->setPosition(sf::Vector2f(1080 * i, 48*4));
        phaseBackGroundSprite.push_back(sprite);
    }

    // Placing zombie enemys in some spaces
    placingEnemys();
}
PhaseMap1::~PhaseMap1()
{
    for (auto* i : phaseBackGroundSprite)
        delete i;
    for (auto* i : zombieEnemys)
        delete i;
    phaseBackGroundSprite.clear();
}

void PhaseMap1::update(int& controller)
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
}

void PhaseMap1::render(sf::RenderWindow& window, int& controller)
{                                               
    sf::View player1View(sf::Vector2f(player1->getPosition()), sf::Vector2f(1120, 672));
    window.setView(player1View);

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
    for (auto* i : zombieEnemys)
        i->render(window);
    player1->draw(window);
    if (player2 != NULL)
        player2->draw(window);
	phaseMapManager.draw(window);
    window.display();
}

void PhaseMap1::renderPhaseBackGround(sf::RenderWindow& window)
{
    for (auto* i : phaseBackGroundSprite)
        window.draw(*i);
}

void PhaseMap1::placingEnemys()
{
    // For the zombies
    Entidade::Enemy::Zombie* z1 = new Entidade::Enemy::Zombie({ 5 * TILE_SIZE, 27 * TILE_SIZE }, { 0, 0 }, 50, 15);
    Entidade::Enemy::Zombie* z2 = new Entidade::Enemy::Zombie({ 32 * TILE_SIZE, 21 * TILE_SIZE }, { 0, 0 }, 50, 15);
    Entidade::Enemy::Zombie* z3 = new Entidade::Enemy::Zombie({ 72 * TILE_SIZE, 26 * TILE_SIZE }, { 0, 0 }, 50, 15);
    Entidade::Enemy::Zombie* z4 = new Entidade::Enemy::Zombie({ 120 * TILE_SIZE, 25 * TILE_SIZE }, { 0, 0 }, 50, 15);
    zombieEnemys.push_back(z1);
    zombieEnemys.push_back(z2);
    zombieEnemys.push_back(z3);
    zombieEnemys.push_back(z4);
}