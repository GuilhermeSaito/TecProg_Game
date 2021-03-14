#include "phaseMapGeneral.h"

using namespace PhaseMap;

PhaseMapGeneral::PhaseMapGeneral(std::string path) :
    phaseMapManager(path),
    player1(NULL),
    player2(NULL)
{
}
PhaseMapGeneral::~PhaseMapGeneral()
{
}

void PhaseMapGeneral::update(int& controller)
{
}

void PhaseMapGeneral::render(sf::RenderWindow& window, int& controller)
{      
}
bool PhaseMapGeneral::loadPhaseMap()
{
    bool flag = phaseMapManager.loadMapTileProprieties();
    collisionManager.setPhaseMapManager(&phaseMapManager);
    return flag;
}

void PhaseMapGeneral::phaseTransition(int& contoller)
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
    player1->setPosition({ 2 * TILE_SIZE, 27 * TILE_SIZE });
    if (player2 != NULL)
        player2->setPosition({ 2 * TILE_SIZE, 27 * TILE_SIZE });
}

void PhaseMapGeneral::setPlayer1(Entidade::Player::Player1* p1)
{
    player1 = p1;
    collisionManager.setPlayer1(p1);
}
void PhaseMapGeneral::setPlayer2(Entidade::Player::Player2* p2)
{
    player2 = p2;
    collisionManager.setPlayer2(p2);
}

void PhaseMapGeneral::ResetAll()
{
    player1 = NULL;
    player2 = NULL;
    collisionManager.ResetAll();
}