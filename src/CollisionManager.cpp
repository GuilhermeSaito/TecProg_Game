#include "CollisionManager.h"

CollisionManager::CollisionManager() : 
	player1(NULL),
	player2(NULL),
	phaseMapManager(NULL)
{
}
CollisionManager::~CollisionManager()
{
	ResetAll();
	phaseMapManager = NULL;
}

void CollisionManager::startVerifyCollision()
{
	player1CollisionX();
	player1CollisionY();
	if (player2 != NULL)
	{
		player2CollisionX();
		player2CollisionY();
	}
}

void CollisionManager::player1CollisionX()
{
	int i, j;
	for (i = player1->getPosition().x / TILE_SIZE; i < ((player1->getPosition().x + player1->getSize().x) / TILE_SIZE); i++)
	{
		if (!phaseMapManager->isValidTile(i, player1->getPosition().y / TILE_SIZE))
			continue;
		PhaseMap::Tiles::Tile* tempTile = phaseMapManager->getTile(i, player1->getPosition().y / 48);
		if (player1->getBoundBox().intersects(tempTile->getBoundBox()))
			player1->collisionInX(tempTile);
	}
}
void CollisionManager::player1CollisionY()
{
	int i, j;
	for (j = player1->getPosition().y / TILE_SIZE; j < ((player1->getPosition().y + player1->getSize().y) / TILE_SIZE); j++)
	{
		if (!phaseMapManager->isValidTile(player1->getPosition().x / TILE_SIZE, j))
			continue;
		PhaseMap::Tiles::Tile* tempTile = phaseMapManager->getTile(player1->getPosition().x / TILE_SIZE, j);
		if (player1->getBoundBox().intersects(tempTile->getBoundBox()))
			player1->collisionInY(tempTile);
		else
			player1->setOnGround(false);
	}
}

void CollisionManager::player2CollisionX()
{
	int i, j;
	for (i = player2->getPosition().x / TILE_SIZE; i < ((player2->getPosition().x + player2->getSize().x) / TILE_SIZE); i++)
	{
		if (!phaseMapManager->isValidTile(i, player2->getPosition().y / TILE_SIZE))
			continue;
		PhaseMap::Tiles::Tile* tempTile = phaseMapManager->getTile(i, player2->getPosition().y / 48);
		if (player2->getBoundBox().intersects(tempTile->getBoundBox()))
			player2->collisionInX(tempTile);
	}
}
void CollisionManager::player2CollisionY()
{
	int i, j;
	for (j = player2->getPosition().y / TILE_SIZE; j < ((player2->getPosition().y + player2->getSize().y) / TILE_SIZE); j++)
	{
		if (!phaseMapManager->isValidTile(player2->getPosition().x / TILE_SIZE, j))
			continue;
		PhaseMap::Tiles::Tile* tempTile = phaseMapManager->getTile(player2->getPosition().x / TILE_SIZE, j);
		if (player2->getBoundBox().intersects(tempTile->getBoundBox()))
			player2->collisionInY(tempTile);
		else
			player2->setOnGround(false);
	}
}

void CollisionManager::setPlayer1(Entidade::Player::Player1* p1) { player1 = p1; }
void CollisionManager::setPlayer2(Entidade::Player::Player2* p2) { player2 = p2; }
void CollisionManager::setPhaseMapManager(PhaseMap::Tiles::PhaseMapManager* phaseMapMa) { phaseMapManager = phaseMapMa; }

void CollisionManager::ResetAll()
{
	player1 = NULL;
	player2 = NULL;
}