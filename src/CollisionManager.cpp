#include "CollisionManager.h"

CollisionManager::CollisionManager() : 
	player1(NULL),
	player2(NULL),
	phaseMapManager(NULL)
{
	this->zombiesList = NULL;
	this->goblinMagesList = NULL;
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
	if (zombiesList != NULL)
	{
		zombiesCollisionX();
		zombiesCollisionY();
	}
	if (goblinMagesList != NULL)
	{
		goblinMagesCollisionX();
		goblinMagesCollisionY();
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

void CollisionManager::zombiesCollisionX()
{
	int i, j;
	Element<Entidade::Enemy::Zombie>* z = this->zombiesList->getFirst();
	while (z != NULL)
	{	
		for (i = z->getInfo()->getPosition().x / TILE_SIZE; i < ((z->getInfo()->getPosition().x + z->getInfo()->getSize().x) / TILE_SIZE); i++)
		{
			if (!phaseMapManager->isValidTile(i, z->getInfo()->getPosition().y / TILE_SIZE))
				continue;
			PhaseMap::Tiles::Tile* tempTile = phaseMapManager->getTile(i, z->getInfo()->getPosition().y / 48);
			if (z->getInfo()->getBoundBox().intersects(tempTile->getBoundBox()))
			{
				z->getInfo()->collisionInX(tempTile);
				z->getInfo()->jump();
			}
		}
		z = z->getNext();
	}
}

void CollisionManager::zombiesCollisionY()
{
	int i, j;
	Element<Entidade::Enemy::Zombie>* z = this->zombiesList->getFirst();
	while (z != NULL)
	{
		for (j = z->getInfo()->getPosition().y / TILE_SIZE; j < ((z->getInfo()->getPosition().y + z->getInfo()->getSize().y) / TILE_SIZE); j++)
		{
			if (!phaseMapManager->isValidTile(z->getInfo()->getPosition().x / TILE_SIZE, j))
				continue;
			PhaseMap::Tiles::Tile* tempTile = phaseMapManager->getTile(z->getInfo()->getPosition().x / TILE_SIZE, j);
			if (z->getInfo()->getBoundBox().intersects(tempTile->getBoundBox()))
				z->getInfo()->collisionInY(tempTile);
			else
				z->getInfo()->setOnGround(false);
		}

		//checa se o objeto passou dos limites em Y do mapa, ou seja, caiu em um buraco
		if (z->getInfo()->getPosition().y >= (28 * TILE_SIZE) + (TILE_SIZE / 3))
		{	
			//aux guarda a informação de z.next, uma vez que ele será deletado logo após na função kill da classe template Lista
			Element<Entidade::Enemy::Zombie>* aux = z->getNext();
			std::cout << "entrou pra matar" << std::endl;
			this->zombiesList->kill(z);
			std::cout << "matou" << std::endl;
			z = aux;
			//continue pois z já recebeu o que seria seu próximo
			continue;
		}
		z = z->getNext();
	}
}

void CollisionManager::goblinMagesCollisionX()
{
	int i, j;
	Element<Entidade::Enemy::GoblinMage>* g = this->goblinMagesList->getFirst();
	while (g != NULL)
	{	
		for (i = g->getInfo()->getPosition().x / TILE_SIZE; i < ((g->getInfo()->getPosition().x + g->getInfo()->getSize().x) / TILE_SIZE); i++)
		{
			if (!phaseMapManager->isValidTile(i, g->getInfo()->getPosition().y / TILE_SIZE))
				continue;
			PhaseMap::Tiles::Tile* tempTile = phaseMapManager->getTile(i, g->getInfo()->getPosition().y / 48);
			if (g->getInfo()->getBoundBox().intersects(tempTile->getBoundBox()))
			{
				g->getInfo()->collisionInX(tempTile);
				g->getInfo()->jump();
			}
		}
		g = g->getNext();
	}
}
void CollisionManager::goblinMagesCollisionY()
{
	int i, j;
	Element<Entidade::Enemy::GoblinMage>* g = this->goblinMagesList->getFirst();
	while (g != NULL)
{
		for (j = g->getInfo()->getPosition().y / TILE_SIZE; j < ((g->getInfo()->getPosition().y + g->getInfo()->getSize().y) / TILE_SIZE); j++)
		{
			if (!phaseMapManager->isValidTile(g->getInfo()->getPosition().x / TILE_SIZE, j))
				continue;
			PhaseMap::Tiles::Tile* tempTile = phaseMapManager->getTile(g->getInfo()->getPosition().x / TILE_SIZE, j);
			if (g->getInfo()->getBoundBox().intersects(tempTile->getBoundBox()))
				g->getInfo()->collisionInY(tempTile);
			else
				g->getInfo()->setOnGround(false);
		}

		//mesma lógica de queda em buraco do que outros inimigos
		if (g->getInfo()->getPosition().y >= (28 * TILE_SIZE) + (TILE_SIZE / 3))
		{	
			Element<Entidade::Enemy::GoblinMage>* aux = g->getNext();
			this->goblinMagesList->kill(g);
			g = aux;
			continue;
		}

		g = g->getNext();
	}
}

void CollisionManager::setPlayer1(Entidade::Player::Player1* p1) { player1 = p1; }
void CollisionManager::setPlayer2(Entidade::Player::Player2* p2) { player2 = p2; }
void CollisionManager::setPhaseMapManager(PhaseMap::Tiles::PhaseMapManager* phaseMapMa) { phaseMapManager = phaseMapMa; }
void CollisionManager::setZombieList(ListElement<Entidade::Enemy::Zombie>* l) { zombiesList = l; }
void CollisionManager::setGoblinMageList(ListElement<Entidade::Enemy::GoblinMage>* l) {goblinMagesList = l;}
void CollisionManager::clearAllLists()
{
	this->zombiesList = NULL;
	this->goblinMagesList = NULL;
}

void CollisionManager::ResetAll()
{
	player1 = NULL;
	player2 = NULL;
	zombiesList = NULL;
	goblinMagesList = NULL;
}