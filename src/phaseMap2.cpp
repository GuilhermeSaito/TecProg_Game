#include "phaseMap2.h"

using namespace PhaseMap;

PhaseMap2::PhaseMap2(sf::RenderWindow *window, std::string path) : PhaseMapGeneral(window, path)
{
    if (!blueOceanPhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/blueOceanPhaseBackGround.png"))
        EXIT_FAILURE;
    // Transforming the image to 1080 x 1440
    for (int i = 0; i < 6; i++)
    {
        sf::Sprite *sprite = new sf::Sprite;
        sprite->setTexture(blueOceanPhaseBackGround);
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

    if (!this->enemiesList.isEmpty())
    {
        this->enemiesList.setNull();
    }

    collisionManager.clearAllLists();

    window = NULL;
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

    if (!this->enemiesList.isEmpty())
        this->enemiesList.update(this->player1);
    // Metodo para ir verificando se tem algum inimigo com hp <= 0, se tiver, tira da lista
    enemyKilled();
}

void PhaseMap2::render(int &controller)
{
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

    //rendering enemies
    if (!this->enemiesList.isEmpty())
        this->enemiesList.render();

    phaseMapManager.draw();
    window->display();
}

void PhaseMap2::renderPhaseBackGround()
{
    for (auto *i : phaseBackGroundSprite)
        window->draw(*i);
}

//places enemies according to player's position on the level
void PhaseMap2::placingEnemies()
{
    if (this->player1->getPosition().x >= 1 * TILE_SIZE && this->enemiesList.getQuantity() == 0)
    {
        Entidade::Enemy::Zombie *z1 = new Entidade::Enemy::Zombie(window, {5 * TILE_SIZE, 27 * TILE_SIZE}, {3, 3}, 50, 15, ZOMBIE_POINTS, ZOMBIE_RESURRECTION_QUANTITY + 10);
        this->enemiesList.include(static_cast<Entidade::EnemyEntity *>(z1));
        Entidade::Enemy::GoblinMage *g1 = new Entidade::Enemy::GoblinMage(window, {7 * TILE_SIZE, 23 * TILE_SIZE}, {3, 3}, 50, 15, GOBLIN_MAGE_POINTS);
        this->enemiesList.include(static_cast<Entidade::ShooterEntity *>(g1));
    }
    if (this->player1->getPosition().x >= 50 * TILE_SIZE && this->enemiesList.getQuantity() == 2)
    {
        Entidade::Enemy::Zombie *z2 = new Entidade::Enemy::Zombie(window, {70 * TILE_SIZE, 21 * TILE_SIZE}, {3, 3}, 50, 15, ZOMBIE_POINTS, ZOMBIE_RESURRECTION_QUANTITY + 5);
        this->enemiesList.include(static_cast<Entidade::EnemyEntity *>(z2));
        Entidade::Enemy::GoblinMage *g2 = new Entidade::Enemy::GoblinMage(window, {78 * TILE_SIZE, 21 * TILE_SIZE}, {3, 3}, 50, 15, GOBLIN_MAGE_POINTS);
        this->enemiesList.include(static_cast<Entidade::ShooterEntity *>(g2));
    }
}
void PhaseMap2::placingObstacles()
{
    // Ainda vou colocar aqui, no update e no render
}