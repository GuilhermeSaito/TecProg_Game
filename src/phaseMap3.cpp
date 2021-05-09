#include "phaseMap3.h"

using namespace PhaseMap;

PhaseMap3::PhaseMap3(sf::RenderWindow *window, std::string path) : PhaseMapGeneral(window, path)
{
    if (!cavePhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/cavePhaseBackGround.png"))
        EXIT_FAILURE;
    // Transforming the image to 1080 x 1440
    for (int i = 0; i < 6; i++)
    {
        sf::Sprite *sprite = new sf::Sprite;
        sprite->setTexture(cavePhaseBackGround);
        sprite->setScale(sf::Vector2f(0.308571429, 0.731335703));
        sprite->setPosition(sf::Vector2f(1080 * i, 48 * 4));
        phaseBackGroundSprite.push_back(sprite);
    }
}
PhaseMap3::~PhaseMap3()
{
    for (auto *i : phaseBackGroundSprite)
        delete i;
    phaseBackGroundSprite.clear();

    if (!this->enemiesList.isEmpty())
        this->enemiesList.setNull();

    window = NULL;
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

    if (!this->enemiesList.isEmpty())
        this->enemiesList.update(this->player1);
    if (!this->obstacleList.isEmpty())
        this->obstacleList.update(this->player1);
    // Metodo para ir verificando se tem algum inimigo com hp <= 0, se tiver, tira da lista
    enemyKilled();
    phaseTransition(controller);
}

void PhaseMap3::render(int &controller)
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

    if (!this->enemiesList.isEmpty())
        this->enemiesList.render();
    if (!this->obstacleList.isEmpty())
        obstacleList.render();

    phaseMapManager.draw();
    window->display();
}

void PhaseMap3::renderPhaseBackGround()
{
    for (auto *i : phaseBackGroundSprite)
        window->draw(*i);
}

void PhaseMap3::placingEnemies()
{
    if (this->player1->getPosition().x >= 1 * TILE_SIZE && this->enemiesList.getQuantity() == 0)
    {
        Entidade::Enemy::Zombie *z1 = new Entidade::Enemy::Zombie(window, {5 * TILE_SIZE, 27 * TILE_SIZE}, {3, 3}, 50, 15, ZOMBIE_POINTS, ZOMBIE_RESURRECTION_QUANTITY + 7);
        this->enemiesList.include(static_cast<Entidade::EnemyEntity *>(z1));
        Entidade::Enemy::GoblinMage *g1 = new Entidade::Enemy::GoblinMage(window, {7 * TILE_SIZE, 23 * TILE_SIZE}, {3, 3}, 50, 15, GOBLIN_MAGE_POINTS);
        this->enemiesList.include(static_cast<Entidade::ShooterEntity *>(g1));
        Entidade::Enemy::FlyingEnemy *f1 = new Entidade::Enemy::FlyingEnemy(window, {7 * TILE_SIZE, 18 * TILE_SIZE}, {3, 3}, 50, 15, FLYING_ENEMY_POINTS);
        this->enemiesList.include(static_cast<Entidade::ShooterEntity *>(f1));
    }
    if (this->player1->getPosition().x >= 50 * TILE_SIZE && this->enemiesList.getQuantity() == 3)
    {
        Entidade::Enemy::Zombie *z2 = new Entidade::Enemy::Zombie(window, {70 * TILE_SIZE, 21 * TILE_SIZE}, {3, 3}, 50, 15, ZOMBIE_POINTS, ZOMBIE_RESURRECTION_QUANTITY + 7);
        this->enemiesList.include(static_cast<Entidade::EnemyEntity *>(z2));
        Entidade::Enemy::Zombie *z3 = new Entidade::Enemy::Zombie(window, {73 * TILE_SIZE, 21 * TILE_SIZE}, {3, 3}, 50, 15, ZOMBIE_POINTS, ZOMBIE_RESURRECTION_QUANTITY + 7);
        this->enemiesList.include(static_cast<Entidade::EnemyEntity *>(z2));
        Entidade::Enemy::GoblinMage *g2 = new Entidade::Enemy::GoblinMage(window, {78 * TILE_SIZE, 21 * TILE_SIZE}, {3, 3}, 50, 15, GOBLIN_MAGE_POINTS);
        this->enemiesList.include(static_cast<Entidade::ShooterEntity *>(g2));
        Entidade::Enemy::GoblinMage *g3 = new Entidade::Enemy::GoblinMage(window, {81 * TILE_SIZE, 21 * TILE_SIZE}, {3, 3}, 50, 15, GOBLIN_MAGE_POINTS);
        this->enemiesList.include(static_cast<Entidade::ShooterEntity *>(g2));
        Entidade::Enemy::FlyingEnemy *f2 = new Entidade::Enemy::FlyingEnemy(window, {65 * TILE_SIZE, 18 * TILE_SIZE}, {3, 3}, 50, 15, FLYING_ENEMY_POINTS);
        this->enemiesList.include(static_cast<Entidade::ShooterEntity *>(f2));
    }
}
void PhaseMap3::placingObstacles()
{
    // Tem esse spikeTrapPoints, pq pode ser q futuramente de para quebrar as traps neh? e.e
    Entidade::Obstacle::SpikeTrap *s1 = new Entidade::Obstacle::SpikeTrap(window, {5 * TILE_SIZE, 27 * TILE_SIZE}, {0, 0}, 1, 5, SPIKE_TRAP_POINTS);
    s1->setWitchTypeOfTrap(SPIKE_TRAP);
    this->obstacleList.include(static_cast<Entidade::EnemyEntity *>(s1));
    Entidade::Obstacle::FallStone *f1 = new Entidade::Obstacle::FallStone(window, {7 * TILE_SIZE, 8 * TILE_SIZE}, {0, 10}, 1, 50, FALL_STONE_POINTS);
    f1->setWitchTypeOfTrap(FALL_STONE);
    this->obstacleList.include(static_cast<Entidade::EnemyEntity *>(f1));

    // Tem esse spikeTrapPoints, pq pode ser q futuramente de para quebrar as traps neh? e.e
    Entidade::Obstacle::SpikeTrap *s2 = new Entidade::Obstacle::SpikeTrap(window, {32 * TILE_SIZE, 27 * TILE_SIZE}, {0, 0}, 1, 5, SPIKE_TRAP_POINTS);
    s2->setWitchTypeOfTrap(SPIKE_TRAP);
    this->obstacleList.include(static_cast<Entidade::EnemyEntity *>(s2));
    Entidade::Obstacle::FallStone *f2 = new Entidade::Obstacle::FallStone(window, {35 * TILE_SIZE, 8 * TILE_SIZE}, {0, 10}, 1, 50, FALL_STONE_POINTS);
    f2->setWitchTypeOfTrap(FALL_STONE);
    this->obstacleList.include(static_cast<Entidade::EnemyEntity *>(f2));

    // Tem esse spikeTrapPoints, pq pode ser q futuramente de para quebrar as traps neh? e.e
    Entidade::Obstacle::SpikeTrap *s3 = new Entidade::Obstacle::SpikeTrap(window, {72 * TILE_SIZE, 27 * TILE_SIZE}, {0, 0}, 1, 5, SPIKE_TRAP_POINTS);
    s3->setWitchTypeOfTrap(SPIKE_TRAP);
    this->obstacleList.include(static_cast<Entidade::EnemyEntity *>(s3));
    Entidade::Obstacle::FallStone *f3 = new Entidade::Obstacle::FallStone(window, {75 * TILE_SIZE, 8 * TILE_SIZE}, {0, 10}, 1, 50, FALL_STONE_POINTS);
    f3->setWitchTypeOfTrap(FALL_STONE);
    this->obstacleList.include(static_cast<Entidade::EnemyEntity *>(f3));

    // Tem esse spikeTrapPoints, pq pode ser q futuramente de para quebrar as traps neh? e.e
    Entidade::Obstacle::SpikeTrap *s4 = new Entidade::Obstacle::SpikeTrap(window, {120 * TILE_SIZE, 27 * TILE_SIZE}, {0, 0}, 1, 5, SPIKE_TRAP_POINTS);
    s4->setWitchTypeOfTrap(SPIKE_TRAP);
    this->obstacleList.include(static_cast<Entidade::EnemyEntity *>(s4));
    Entidade::Obstacle::FallStone *f4 = new Entidade::Obstacle::FallStone(window, {122 * TILE_SIZE, 8 * TILE_SIZE}, {0, 10}, 1, 50, FALL_STONE_POINTS);
    f4->setWitchTypeOfTrap(FALL_STONE);
    this->obstacleList.include(static_cast<Entidade::EnemyEntity *>(f4));

    // Tem esse spikeTrapPoints, pq pode ser q futuramente de para quebrar as traps neh? e.e
    Entidade::Obstacle::SpikeTrap *s5 = new Entidade::Obstacle::SpikeTrap(window, {123 * TILE_SIZE, 27 * TILE_SIZE}, {0, 0}, 1, 5, SPIKE_TRAP_POINTS);
    s5->setWitchTypeOfTrap(SPIKE_TRAP);
    this->obstacleList.include(static_cast<Entidade::EnemyEntity *>(s5));
    Entidade::Obstacle::FallStone *f5 = new Entidade::Obstacle::FallStone(window, {125 * TILE_SIZE, 8 * TILE_SIZE}, {0, 10}, 1, 50, FALL_STONE_POINTS);
    f5->setWitchTypeOfTrap(FALL_STONE);
    this->obstacleList.include(static_cast<Entidade::EnemyEntity *>(f5));
}