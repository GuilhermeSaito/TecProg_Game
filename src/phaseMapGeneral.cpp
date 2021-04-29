#include "phaseMapGeneral.h"

using namespace PhaseMap;

PhaseMapGeneral::PhaseMapGeneral(sf::RenderWindow *window, std::string path) : phaseMapManager(window, path),
                                                                               player1(NULL),
                                                                               player2(NULL),
                                                                               enemiesList(),
                                                                               obstacleList(),
                                                                               Menu(window)
{
    player1View.setSize(sf::Vector2f(1120, 672));
}
PhaseMapGeneral::~PhaseMapGeneral()
{
    window = NULL;
}

void PhaseMapGeneral::update(int &controller)
{
}

void PhaseMapGeneral::render(int &controller)
{
}
bool PhaseMapGeneral::loadPhaseMap()
{
    bool flag = phaseMapManager.loadMapTileProprieties();
    collisionManager.setPhaseMapManager(&phaseMapManager);
    return flag;
}

void PhaseMapGeneral::setViewInPlayer1(const int controller)
{
    if (player1 != NULL)
        if ((player1->getPosition().x - (12 * TILE_SIZE)) < 0)
            player1View.setCenter(sf::Vector2f(12 * TILE_SIZE, 23 * TILE_SIZE));
        else if (player1->getPosition().x > 123 * TILE_SIZE)
            player1View.setCenter(sf::Vector2f(123 * TILE_SIZE, 23 * TILE_SIZE));
        else if (player1->getPosition().y < 21 * TILE_SIZE)
        {
            if (controller != PHASE4)
                player1View.setCenter(sf::Vector2f(player1->getPosition().x, player1->getPosition().y));
        }
        else
            player1View.setCenter(sf::Vector2f(player1->getPosition().x, 23 * TILE_SIZE));
    // Pegando o View aqui e colocando no player 1 pois eu preciso saber o center do view para colocar o score certinho na tela
    player1->setPlayer1View(&player1View);
    window->setView(player1View);
}

void PhaseMapGeneral::phaseTransition(int &contoller)
{
    if (player2 != NULL)
        if (player2->getPosition().x >= 131 * TILE_SIZE)
        {
            resetEverythingForTransition();
            contoller++;
        }
    if (player1->getPosition().x >= 131 * TILE_SIZE)
    {
        resetEverythingForTransition();
        contoller++;
    }
}

const bool PhaseMapGeneral::isPlayerDead()
{
    if ((player1->getPosition().y >= (28 * TILE_SIZE) + (TILE_SIZE / 3)) || (player1->getHp() < 0))
        return true;
    if (player2 != NULL)
        if ((player2->getPosition().y >= (28 * TILE_SIZE) + (TILE_SIZE / 3)) || player2->getHp() < 0)
            return true;
    return false;
}

void PhaseMapGeneral::enemyKilled()
{
    Lists::Element<Entidade::EnemyEntity> *g = this->enemiesList.getFirst();
    Lists::Element<Entidade::EnemyEntity> *aux = g;
    while (g != NULL)
    {
        g = g->getNext();
        if (aux->getInfo()->getHp() <= 0)
        {
            player1->updateScore(aux->getInfo()->getPoints());
            enemiesList.kill(aux);
        }
        aux = g;
    }
}

const bool PhaseMapGeneral::isGameClear()
{
    return enemiesList.isEmpty();
}

void PhaseMapGeneral::placingEnemies()
{
}
void PhaseMapGeneral::placingObstacles()
{
}

void PhaseMapGeneral::resetEverythingForTransition()
{
    player1->setPosition({2 * TILE_SIZE, 27 * TILE_SIZE});
    if (player2 != NULL)
        player2->setPosition({2 * TILE_SIZE, 27 * TILE_SIZE});

    if (!enemiesList.isEmpty())
        enemiesList.setNull();
    if (!obstacleList.isEmpty())
        obstacleList.setNull();

    collisionManager.clearAllLists();
}

void PhaseMapGeneral::setPlayer1(Entidade::Player::Player1 *p1)
{
    player1 = p1;
    collisionManager.setPlayer1(p1);
}
void PhaseMapGeneral::setPlayer2(Entidade::Player::Player2 *p2)
{
    player2 = p2;
    collisionManager.setPlayer2(p2);
}

void PhaseMapGeneral::loadListsInCollision()
{
    collisionManager.setEnemiesList(&enemiesList);
    collisionManager.setObstacleList(&obstacleList);
}

Lists::EnemiesList *PhaseMapGeneral::getEnemiesList()
{
    return &enemiesList;
}
Lists::ObstacleList *PhaseMapGeneral::getObstacleList()
{
    return &obstacleList;
}

void PhaseMapGeneral::ResetAll()
{
    player1 = NULL;
    player2 = NULL;
    if (!enemiesList.isEmpty())
        enemiesList.setNull();
    collisionManager.ResetAll();
}