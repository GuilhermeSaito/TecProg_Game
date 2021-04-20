#include "phaseMapGeneral.h"

using namespace PhaseMap;

PhaseMapGeneral::PhaseMapGeneral(std::string path) : phaseMapManager(path),
                                                     player1(NULL),
                                                     player2(NULL),
                                                     enemiesList()
{
    player1View.setSize(sf::Vector2f(1120, 672));
}
PhaseMapGeneral::~PhaseMapGeneral()
{
}

void PhaseMapGeneral::update(int &controller)
{
}

void PhaseMapGeneral::render(sf::RenderWindow &window, int &controller)
{
}
bool PhaseMapGeneral::loadPhaseMap()
{
    bool flag = phaseMapManager.loadMapTileProprieties();
    collisionManager.setPhaseMapManager(&phaseMapManager);
    return flag;
}

void PhaseMapGeneral::setViewInPlayer1(sf::RenderWindow &window, const int controller)
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
    window.setView(player1View);
}

void PhaseMapGeneral::phaseTransition(int &contoller)
{
    if (contoller != PHASE4)
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
}

bool PhaseMapGeneral::isPlayerDead()
{
    if (player1->getPosition().y >= (28 * TILE_SIZE) + (TILE_SIZE / 3))
        return true;
    if (player2 != NULL)
        if (player2->getPosition().y >= (28 * TILE_SIZE) + (TILE_SIZE / 3))
            return true;
    return false;
}

void PhaseMapGeneral::resetEverythingForTransition()
{
    player1->setPosition({2 * TILE_SIZE, 27 * TILE_SIZE});
    if (player2 != NULL)
        player2->setPosition({2 * TILE_SIZE, 27 * TILE_SIZE});

    if (!enemiesList.isEmpty())
        enemiesList.setNull();

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

void PhaseMapGeneral::loadEnemiesListInCollision()
{
    collisionManager.setEnemiesList(&enemiesList);
}
EnemiesList* PhaseMapGeneral::getEnemiesList()
{
    return &enemiesList;
}

void PhaseMapGeneral::ResetAll()
{
    player1 = NULL;
    player2 = NULL;
    if (!enemiesList.isEmpty())
        enemiesList.setNull();
    collisionManager.ResetAll();
}