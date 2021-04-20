#include "phaseMap4.h"

using namespace PhaseMap;

PhaseMap4::PhaseMap4(std::string path) : PhaseMapGeneral(path),
                                         clock(),
                                         elapsed()
{
    // Transforming the image to 1080 x 1440
    // Esse aqui vou colocar em dimensoes um pouco diferentes
    for (int i = 0; i < 6; i++)
    {
        sf::Sprite *sprite = new sf::Sprite;
        sprite->setTexture(*(Data::getInstance()->getDathPhaseBackGround()));
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

    phaseTransition(controller);
}

void PhaseMap4::render(sf::RenderWindow &window, int &controller)
{
    // Soh nessa fase que eu nao vou atualizar o view se a posicao do player estiver muito alta
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

    if (!this->enemiesList.isEmpty())
        this->enemiesList.render(window);

    phaseMapManager.draw(window);
    window.display();
}

void PhaseMap4::renderPhaseBackGround(sf::RenderWindow &window)
{
    for (auto *i : phaseBackGroundSprite)
        window.draw(*i);
}

void PhaseMap4::placingEnemies()
{
    this->elapsed = this->clock.getElapsedTime();

    if (elapsed.asSeconds() >= 4 && this->enemiesList.getQuantity() == 0)
    {
        std::cout << elapsed.asSeconds() << std::endl;
        Entidade::Enemy::Boss *b = new Entidade::Enemy::Boss({50 * TILE_SIZE, 18 * TILE_SIZE}, {3, 3}, 300, 30.f);
        this->enemiesList.include(static_cast<Entidade::EnemyEntity*>(b));
    }
    if (elapsed.asSeconds() >= 15 && this->enemiesList.getQuantity() == 1)
    {
        std::cout << elapsed.asSeconds() << std::endl;
        Entidade::Enemy::FlyingEnemy *f1 = new Entidade::Enemy::FlyingEnemy({7 * TILE_SIZE, 18 * TILE_SIZE}, {3, 3}, 50, 15);
        this->enemiesList.include(static_cast<Entidade::EnemyEntity*>(f1));
    }
    if (elapsed.asSeconds() >= 25 && this->enemiesList.getQuantity() == 2)
    {
        std::cout << elapsed.asSeconds() << std::endl;
        Entidade::Enemy::FlyingEnemy *f2 = new Entidade::Enemy::FlyingEnemy({65 * TILE_SIZE, 18 * TILE_SIZE}, {3, 3}, 50, 15);
        this->enemiesList.include(static_cast<Entidade::EnemyEntity*>(f2));
    }
}

void PhaseMap4::resetClock()
{
    this->clock.restart();
}
