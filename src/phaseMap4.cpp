#include "phaseMap4.h"

using namespace PhaseMap;

PhaseMap4::PhaseMap4(sf::RenderWindow *window, std::string path) : PhaseMapGeneral(window, path),
                                                                   clock(),
                                                                   elapsed()
{
    if (!deathPhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/deathPhaseBackGround.png"))
        EXIT_FAILURE;
    // Transforming the image to 1080 x 1440
    // Esse aqui vou colocar em dimensoes um pouco diferentes
    for (int i = 0; i < 6; i++)
    {
        sf::Sprite *sprite = new sf::Sprite;
        sprite->setTexture(deathPhaseBackGround);
        sprite->setScale(sf::Vector2f(1, 1));
        sprite->setPosition(sf::Vector2f(1280 * i, 48 * 16));
        phaseBackGroundSprite.push_back(sprite);
    }
}
PhaseMap4::~PhaseMap4()
{
    for (auto *i : phaseBackGroundSprite)
        delete i;
    phaseBackGroundSprite.clear();

    if (!this->enemiesList.isEmpty())
        this->enemiesList.setNull();

    window = NULL;
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

    if (!this->enemiesList.isEmpty())
        this->enemiesList.update(this->player1);
    if (!this->obstacleList.isEmpty())
        this->obstacleList.update(this->player1);

    //-------------------------------- Esse metodo precisa ser melhorado, ele nao volta ao normal na 4 fase se terminar------------------------
    if (isGameClear() && elapsed.asSeconds() >= 8)
    {
        controller = RANK;
        return;
    }
    // Metodo para ir verificando se tem algum inimigo com hp <= 0, se tiver, tira da lista
    enemyKilled();
}

void PhaseMap4::render(int &controller)
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
    if (!this->obstacleList.isEmpty())
        obstacleList.render();

    phaseMapManager.draw();
    window->display();
}

void PhaseMap4::renderPhaseBackGround()
{
    for (auto *i : phaseBackGroundSprite)
        window->draw(*i);
}

void PhaseMap4::placingEnemies()
{
    this->elapsed = this->clock.getElapsedTime();

    if (elapsed.asSeconds() >= 4 && this->enemiesList.getQuantity() == 0)
    {
        Entidade::Enemy::Boss *b = new Entidade::Enemy::Boss(window, {50 * TILE_SIZE, 18 * TILE_SIZE}, {3, 3}, 300, 30.f, BOSS_POINTS);
        this->enemiesList.include(static_cast<Entidade::ShooterEntity *>(b));
        resetClock();
    }
    if (elapsed.asSeconds() >= 15 && this->enemiesList.getQuantity() == 1)
    {
        Entidade::Enemy::FlyingEnemy *f1 = new Entidade::Enemy::FlyingEnemy(window, {7 * TILE_SIZE, 18 * TILE_SIZE}, {3, 3}, 50, 15, FLYING_ENEMY_POINTS);
        this->enemiesList.include(static_cast<Entidade::ShooterEntity *>(f1));
    }
    if (elapsed.asSeconds() >= 25 && this->enemiesList.getQuantity() == 2)
    {
        Entidade::Enemy::FlyingEnemy *f2 = new Entidade::Enemy::FlyingEnemy(window, {65 * TILE_SIZE, 18 * TILE_SIZE}, {3, 3}, 50, 15, FLYING_ENEMY_POINTS);
        this->enemiesList.include(static_cast<Entidade::ShooterEntity *>(f2));
    }
}
void PhaseMap4::placingObstacles()
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

void PhaseMap4::resetClock()
{
    this->clock.restart();
}
