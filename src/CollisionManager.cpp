#include "CollisionManager.h"

CollisionManager::CollisionManager() : 
	player1(NULL),
	player2(NULL),
	phaseMapManager(NULL),
	zombiesList(NULL),
	goblinMagesList(NULL),
	flyingEnemiesList(NULL),
	boss(NULL)
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
	if (zombiesList != NULL)
	{
		zombiesCollisionX();
		zombiesCollisionY();
	}
	if (goblinMagesList != NULL)
	{
		goblinMagesCollisionX();
		goblinMagesCollisionY();
		goblinMagesProjectiliesCollision();
	}
	if (flyingEnemiesList != NULL)
	{
		flyingEnemiesCollisionX();
		flyingEnemiesCollisionY();
		flyingEnemiesProjectilesCollision();
	}
	if (boss != NULL)
	{
		bossCollisionX();
		bossCollisionY();
		bossProjectilesCollision();
	}
}

void CollisionManager::player1CollisionX()
{
	int i = 0, j = 0;
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
	int i = 0, j = 0;
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
	int i = 0, j = 0;
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
	int i = 0, j = 0;
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
	int i = 0, j = 0;
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
	int i = 0, j = 0;
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
	int i = 0, j = 0;
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
	int i = 0, j = 0;
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
//Checking wrather any projectile hit the player. If so, this one gets deleted and the player loses health.
void CollisionManager::goblinMagesProjectiliesCollision()
{
	Element<Entidade::Enemy::GoblinMage>* g = this->goblinMagesList->getFirst();
	while (g != NULL)
	{
		Element<Projectile>* p = g->getInfo()->getProjectiles()->getFirst();
		while(p != NULL)
		{
			if (p->getInfo()->getBoundBox().intersects(player1->getBoundBox()))
			{
				player1->setHp(player1->getHp() - 5);
				Element<Projectile>* p2 = p->getNext();
				g->getInfo()->getProjectiles()->kill(p);
				p = p2;
				continue;
			}

			p = p->getNext();
		}

		g = g->getNext();
	}
}

void CollisionManager::flyingEnemiesCollisionX()
{
	int i = 0, j = 0;
	Element<Entidade::Enemy::FlyingEnemy>* f = this->flyingEnemiesList->getFirst();
	while (f != NULL)
	{	
		for (i = f->getInfo()->getPosition().x / TILE_SIZE; i < ((f->getInfo()->getPosition().x + f->getInfo()->getSize().x) / TILE_SIZE); i++)
		{
			if (!phaseMapManager->isValidTile(i, f->getInfo()->getPosition().y / TILE_SIZE))
				continue;
			PhaseMap::Tiles::Tile* tempTile = phaseMapManager->getTile(i, f->getInfo()->getPosition().y / 48);
			if (f->getInfo()->getBoundBox().intersects(tempTile->getBoundBox()))
			{
				f->getInfo()->collisionInX(tempTile);
				f->getInfo()->jump();
			}
		}
		f = f->getNext();
	}
}
void CollisionManager::flyingEnemiesCollisionY()
{
	int i = 0, j = 0;
	Element<Entidade::Enemy::FlyingEnemy>* f = this->flyingEnemiesList->getFirst();
	while (f != NULL)
	{
		for (j = f->getInfo()->getPosition().y / TILE_SIZE; j < ((f->getInfo()->getPosition().y + f->getInfo()->getSize().y) / TILE_SIZE); j++)
		{
			if (!phaseMapManager->isValidTile(f->getInfo()->getPosition().x / TILE_SIZE, j))
				continue;
			PhaseMap::Tiles::Tile* tempTile = phaseMapManager->getTile(f->getInfo()->getPosition().x / TILE_SIZE, j);
			if (f->getInfo()->getBoundBox().intersects(tempTile->getBoundBox()))
				f->getInfo()->collisionInY(tempTile);
			else
				f->getInfo()->setOnGround(false);
		}

		f = f->getNext();
	}
}
//Checking wrather any projectile hit the player. If so, this one gets deleted and the player loses health.
void CollisionManager::flyingEnemiesProjectilesCollision()
{
	Element<Entidade::Enemy::FlyingEnemy>* f = this->flyingEnemiesList->getFirst();
	while (f != NULL)
	{
		Element<Projectile>* p = f->getInfo()->getProjectiles()->getFirst();
		while(p != NULL)
		{
			if (p->getInfo()->getBoundBox().intersects(player1->getBoundBox()))
			{
				player1->setHp(player1->getHp() - 5);
				Element<Projectile>* p2 = p->getNext();
				f->getInfo()->getProjectiles()->kill(p);
				p = p2;
				continue;
			}

			p = p->getNext();
		}

		f = f->getNext();
	}
}

void CollisionManager::bossCollisionX()
{
	int i = 0, j = 0;
	for (i = boss->getPosition().x / TILE_SIZE; i < ((boss->getPosition().x + boss->getSize().x) / TILE_SIZE); i++)
		{
			if (!phaseMapManager->isValidTile(i, boss->getPosition().y / TILE_SIZE))
				continue;
			PhaseMap::Tiles::Tile* tempTile = phaseMapManager->getTile(i, boss->getPosition().y / 48);
			if (boss->getBoundBox().intersects(tempTile->getBoundBox()) && boss->getPosition().x > 2*TILE_SIZE)
			{
				boss->collisionInX(tempTile);
				boss->jump();
			}
		}
}
void CollisionManager::bossCollisionY()
{
	int i = 0, j = 0;
	for (j = boss->getPosition().y / TILE_SIZE; j < ((boss->getPosition().y + boss->getSize().y) / TILE_SIZE); j++)
		{
			if (!phaseMapManager->isValidTile(boss->getPosition().x / TILE_SIZE, j))
				continue;
			PhaseMap::Tiles::Tile* tempTile = phaseMapManager->getTile(boss->getPosition().x / TILE_SIZE, j);
			if (boss->getBoundBox().intersects(tempTile->getBoundBox()))
				boss->collisionInY(tempTile);
			else
				boss->setOnGround(false);
		}
}
void CollisionManager::bossProjectilesCollision()
{
	Element<Projectile>* p = boss->getProjectiles()->getFirst();
		while(p != NULL)
		{
			if (p->getInfo()->getBoundBox().intersects(player1->getBoundBox()))
			{
				player1->setHp(player1->getHp() - 7);
				Element<Projectile>* p2 = p->getNext();
				boss->getProjectiles()->kill(p);
				p = p2;
				continue;
			}

			p = p->getNext();
		}
}

void CollisionManager::setPlayer1(Entidade::Player::Player1* p1) { player1 = p1; }
void CollisionManager::setPlayer2(Entidade::Player::Player2* p2) { player2 = p2; }
void CollisionManager::setPhaseMapManager(PhaseMap::Tiles::PhaseMapManager* phaseMapMa) { phaseMapManager = phaseMapMa; }
void CollisionManager::setZombieList(ListElement<Entidade::Enemy::Zombie>* l) { zombiesList = l; }
void CollisionManager::setGoblinMageList(ListElement<Entidade::Enemy::GoblinMage>* l) {goblinMagesList = l;}
void CollisionManager::setFlyingEnemiesList(ListElement<Entidade::Enemy::FlyingEnemy>* l) {flyingEnemiesList = l;}
void CollisionManager::setBoss(Entidade::Enemy::Boss* b) {this->boss = b;}
void CollisionManager::clearAllLists()
{
	if (this->zombiesList != NULL && !this->zombiesList->isEmpty())
		this->zombiesList->setNull();

	if (this->goblinMagesList != NULL && !this->goblinMagesList->isEmpty())
		this->goblinMagesList->setNull();

	if (this->flyingEnemiesList != NULL && !this->flyingEnemiesList->isEmpty())
		this->flyingEnemiesList->setNull();

	this->zombiesList = NULL;
	this->goblinMagesList = NULL;
	this->flyingEnemiesList = NULL;
	this->boss = NULL;
}

void CollisionManager::ResetAll()
{
	player1 = NULL;
	player2 = NULL;
	zombiesList = NULL;
	goblinMagesList = NULL;
	flyingEnemiesList = NULL;
	boss = NULL;
}