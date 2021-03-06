#include "CollisionManager.h"

CollisionManager::CollisionManager() : player1(NULL),
									   player2(NULL),
									   phaseMapManager(NULL),
									   enemiesList(NULL),
									   obstacleList(NULL),
									   threadedBosses(NULL)
{
}
CollisionManager::~CollisionManager()
{
	ResetAll();
	phaseMapManager = NULL;
	threadedBosses = NULL;
}

void CollisionManager::startVerifyCollision()
{

	if (player1 != NULL)
	{
		player1CollisionX();
		player1CollisionY();
	}
	if (player2 != NULL)
	{
		player2CollisionX();
		player2CollisionY();
	}

	if (enemiesList != NULL)
	{
		enemiesCollisionX();
		enemiesCollisionY();
		enemiesProjectiliesCollision();
		enemyCollidesPlayer();
		playerCollidesEnemy();
	}

	if (obstacleList != NULL)
	{
		obstacleCollidesPlayers();
		obstacleCollisionY();
	}

	//if (threadedBosses != NULL)
	//{
	//threadedBossCollisionX();
	//threadedBossCollisionY();
	//if (player1 != NULL) // Dentro da funcao ja verifica o player 2
	//	threadedBossCollisionPlayer();
	//}
}

void CollisionManager::player1CollisionX()
{
	int i = 0, j = 0;

	for (i = player1->getPosition().x / TILE_SIZE; i < ((player1->getPosition().x + player1->getSize().x) / TILE_SIZE); i++)
	{

		if (!phaseMapManager->isValidTile(i, player1->getPosition().y / TILE_SIZE))
			continue;

		PhaseMap::Tiles::Tile *tempTile = phaseMapManager->getTile(i, player1->getPosition().y / 48);
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
		PhaseMap::Tiles::Tile *tempTile = phaseMapManager->getTile(player1->getPosition().x / TILE_SIZE, j);
		if (player1->getBoundBox().intersects(tempTile->getBoundBox()))
			player1->collisionInY(tempTile);
		else
			player1->setOnGround(false);
		// O MOTIVO DO PORQUE O PERSONAGEM FICA INDO PARA CIMA E PARA BAIXO, E POR CAUSA DESSE ELSE.
		// MAS, SE NAO TIVER ELE, O PLAYER PODE DAR UMA DE MOISES E IR FLUTUANDO NO AR
	}
}

void CollisionManager::player2CollisionX()
{
	int i = 0, j = 0;
	for (i = player2->getPosition().x / TILE_SIZE; i < ((player2->getPosition().x + player2->getSize().x) / TILE_SIZE); i++)
	{
		if (!phaseMapManager->isValidTile(i, player2->getPosition().y / TILE_SIZE))
			continue;
		PhaseMap::Tiles::Tile *tempTile = phaseMapManager->getTile(i, player2->getPosition().y / 48);
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
		PhaseMap::Tiles::Tile *tempTile = phaseMapManager->getTile(player2->getPosition().x / TILE_SIZE, j);
		if (player2->getBoundBox().intersects(tempTile->getBoundBox()))
			player2->collisionInY(tempTile);
		else
			player2->setOnGround(false);
	}
}

void CollisionManager::enemiesCollisionX()
{
	int i = 0, j = 0;
	Lists::Element<Entidade::EnemyEntity> *z = this->enemiesList->getFirst();
	while (z != NULL)
	{
		for (i = z->getInfo()->getPosition().x / TILE_SIZE; i < ((z->getInfo()->getPosition().x + z->getInfo()->getSize().x) / TILE_SIZE); i++)
		{
			if (!phaseMapManager->isValidTile(i, z->getInfo()->getPosition().y / TILE_SIZE))
				continue;
			PhaseMap::Tiles::Tile *tempTile = phaseMapManager->getTile(i, z->getInfo()->getPosition().y / 48);
			if (z->getInfo()->getBoundBox().intersects(tempTile->getBoundBox()))
			{
				z->getInfo()->collisionInX(tempTile);
				z->getInfo()->jump();
			}
		}
		z = z->getNext();
	}
}

void CollisionManager::enemiesCollisionY()
{
	int i = 0, j = 0;
	Lists::Element<Entidade::EnemyEntity> *z = this->enemiesList->getFirst();
	while (z != NULL)
	{
		for (j = z->getInfo()->getPosition().y / TILE_SIZE; j < ((z->getInfo()->getPosition().y + z->getInfo()->getSize().y) / TILE_SIZE); j++)
		{
			if (!phaseMapManager->isValidTile(z->getInfo()->getPosition().x / TILE_SIZE, j))
				continue;
			PhaseMap::Tiles::Tile *tempTile = phaseMapManager->getTile(z->getInfo()->getPosition().x / TILE_SIZE, j);
			if (z->getInfo()->getBoundBox().intersects(tempTile->getBoundBox()))
				z->getInfo()->collisionInY(tempTile);
			else
				z->getInfo()->setOnGround(false);
		}

		//checa se o objeto passou dos limites em Y do mapa, ou seja, caiu em um buraco
		if (z->getInfo()->getPosition().y >= (28 * TILE_SIZE) + (TILE_SIZE / 3))
		{
			//aux guarda a informa????o de z.next, uma vez que ele ser?? deletado logo ap??s na fun????o kill da classe template Lista
			Lists::Element<Entidade::EnemyEntity> *aux = z->getNext();
			this->enemiesList->kill(z);
			z = aux;
			//continue pois z j?? recebeu o que seria seu pr??ximo
			continue;
		}
		z = z->getNext();
	}
}

//Checking wrather any projectile hit the player. If so, this one gets deleted and the player loses health.
void CollisionManager::enemiesProjectiliesCollision()
{
	Lists::Element<Entidade::EnemyEntity> *g = this->enemiesList->getFirst();
	while (g != NULL)
	{
		if (g->getInfo()->getHasProjectiles() == true)
		{
			Lists::Element<Projectile> *p = g->getInfo()->getProjectiles()->getFirst();
			while (p != NULL)
			{
				if (p->getInfo()->getBoundBox().intersects(player1->getBoundBox()))
				{
					player1->setHp(player1->getHp() - 5);
					Lists::Element<Projectile> *p2 = p->getNext();
					g->getInfo()->getProjectiles()->kill(p);
					p = p2;
					continue;
				}

				p = p->getNext();
			}
		}

		g = g->getNext();
	}
}

void CollisionManager::enemyCollidesPlayer()
{
	sf::Time elapsed = clockEnemyAttack.getElapsedTime();
	Lists::Element<Entidade::EnemyEntity> *g = this->enemiesList->getFirst();
	while (g != NULL)
	{
		// O clockEnemyAttack soh pode resetar se atingir algum dos players
		if (g->getInfo()->getBoundBox().intersects(player1->getBoundBox()))
		{
			//checando se o inimigo est?? colidindo com o player
			if (player1->getSpeed().x > 0)
				player1->setPosition({g->getInfo()->getBoundBox().left - player1->getBoundBox().width, player1->getPosition().y});
			else if (player1->getSpeed().x < 0 && player1->getSpeed().y > 0.6)
				player1->setPosition({g->getInfo()->getBoundBox().left + player1->getBoundBox().width, player1->getPosition().y});
			else if (player1->getSpeed().x < 0)
				player1->setPosition({g->getInfo()->getBoundBox().left + player1->getBoundBox().width, player1->getPosition().y});
			player1->setSpeed({0, player1->getSpeed().y});
			g->getInfo()->setSpeed({0, g->getInfo()->getSpeed().y});

			if (elapsed.asSeconds() >= 1)
			{
				player1->setHp(player1->getHp() - g->getInfo()->getAttackDamage());
				clockEnemyAttack.restart();
			}
		}
		if (player2 != NULL)
			if (g->getInfo()->getBoundBox().intersects(player2->getBoundBox()))
			{
				if (player2->getSpeed().x > 0)
					player2->setPosition({g->getInfo()->getBoundBox().left - player2->getBoundBox().width, player2->getPosition().y});
				else if (player2->getSpeed().x < 0 && player2->getSpeed().y > 0.6)
					player2->setPosition({g->getInfo()->getBoundBox().left + player2->getBoundBox().width, player2->getPosition().y});
				else if (player2->getSpeed().x < 0)
					player2->setPosition({g->getInfo()->getBoundBox().left + player2->getBoundBox().width, player2->getPosition().y});
				player2->setSpeed({0, player1->getSpeed().y});
				g->getInfo()->setSpeed({0, g->getInfo()->getSpeed().y});

				if (elapsed.asSeconds() >= 1)
				{
					player2->setHp(player2->getHp() - g->getInfo()->getAttackDamage());
					clockEnemyAttack.restart();
				}
			}
		g = g->getNext();
	}
	// Nao sei se tem problema em o clock estourar, mas vou previnir
	if (elapsed.asSeconds() >= 100)
		clockEnemyAttack.restart();
}

void CollisionManager::playerCollidesEnemy()
{
	sf::Time elapsed = clockPlayerAttack.getElapsedTime();
	Lists::Element<Entidade::EnemyEntity> *g = this->enemiesList->getFirst();
	while (g != NULL)
	{
		// Somente 1 dos players pode dar dano e.e E o dano do player2 eh maior
		if ((elapsed.asSeconds() >= 0.01))
		{
			//checando se o player t?? na cabe??a do inimigo e fazendo a colis??o caso sim
			if (!player1->getOnGround() && abs(player1->getPosition().x - g->getInfo()->getPosition().x) <= (g->getInfo()->getBoundBox().width + 10))
			{
				if (player1->getBoundBox().intersects(g->getInfo()->getBoundBox()))
				{
					g->getInfo()->setHp(g->getInfo()->getHp() - player1->getAttackDamage());
					player1->setOnGround(true);
					player1->setSpeed({player1->getSpeed().x, 0});
					player1->jump();
					clockPlayerAttack.restart();
					clockEnemyAttack.restart();
				}
			}
			else if (player2 != NULL)
				if (!player2->getOnGround() && abs(player1->getPosition().x - g->getInfo()->getPosition().x) <= (g->getInfo()->getBoundBox().width + 10))
					if (player2->getBoundBox().intersects(g->getInfo()->getBoundBox()))
					{
						g->getInfo()->setHp(g->getInfo()->getHp() - player2->getAttackDamage());
						player2->setOnGround(true);
						player2->setSpeed({player1->getSpeed().x, 0});
						player2->jump();
						clockPlayerAttack.restart();
						clockEnemyAttack.restart();
					}
		}
		g = g->getNext();
	}
	// Nao sei se tem problema em o clock estourar, mas vou previnir
	if (elapsed.asSeconds() >= 100)
		clockPlayerAttack.restart();
}

void CollisionManager::obstacleCollidesPlayers()
{
	sf::Time elapsed1 = spikeTrapAttack1.getElapsedTime();
	sf::Time elapsed2 = spikeTrapAttack2.getElapsedTime();
	Lists::Element<Entidade::EnemyEntity> *g = this->obstacleList->getFirst();
	while (g != NULL)
	{
		if (g->getInfo()->getWitchTypeOfTrahp() == SPIKE_TRAP)
		{
			if ((g->getInfo()->getBoundBox().intersects(player1->getBoundBox())) && (elapsed1.asSeconds() >= 0.3))
			{
				player1->setHp(0);
				spikeTrapAttack1.restart();
			}
			if (player2 != NULL)
				if ((g->getInfo()->getBoundBox().intersects(player2->getBoundBox())) && (elapsed2.asSeconds() >= 0.3))
				{
					player2->setHp(0);
					spikeTrapAttack2.restart();
				}
		}
		else
		{
			if ((g->getInfo()->getBoundBox().intersects(player1->getBoundBox())) && (!g->getInfo()->getOnGround()))
				player1->setHp(player1->getHp() - g->getInfo()->getAttackDamage());
			if (player2 != NULL)
				if ((g->getInfo()->getBoundBox().intersects(player2->getBoundBox())) && (!g->getInfo()->getOnGround()))
					player2->setHp(player2->getHp() - g->getInfo()->getAttackDamage());
		}
		g = g->getNext();
	}
	if (elapsed1.asSeconds() >= 100)
		clockPlayerAttack.restart();
	if (elapsed2.asSeconds() >= 100)
		clockPlayerAttack.restart();
}
void CollisionManager::obstacleCollisionY()
{
	int i = 0, j = 0;
	Lists::Element<Entidade::EnemyEntity> *g = this->obstacleList->getFirst();
	while (g != NULL)
	{
		if (g->getInfo()->getWitchTypeOfTrahp() == FALL_STONE)
			for (j = g->getInfo()->getPosition().y / TILE_SIZE; j < ((g->getInfo()->getPosition().y + g->getInfo()->getSize().y) / TILE_SIZE); j++)
			{
				if (!phaseMapManager->isValidTile(g->getInfo()->getPosition().x / TILE_SIZE, j))
					continue;
				PhaseMap::Tiles::Tile *tempTile = phaseMapManager->getTile(g->getInfo()->getPosition().x / TILE_SIZE, j);
				if (g->getInfo()->getBoundBox().intersects(tempTile->getBoundBox()))
					g->getInfo()->collisionInY(tempTile);
			}
		g = g->getNext();
	}
}

void CollisionManager::threadedBossCollisionX()
{
	int i = 0, j = 0;
	for (i = threadedBosses->getPosition().x / TILE_SIZE; i < ((threadedBosses->getPosition().x + threadedBosses->getSize().x) / TILE_SIZE); i++)
	{
		if (!phaseMapManager->isValidTile(i, threadedBosses->getPosition().y / TILE_SIZE))
			continue;
		PhaseMap::Tiles::Tile *tempTile = phaseMapManager->getTile(i, threadedBosses->getPosition().y / 48);
		if (threadedBosses->getBoundBox().intersects(tempTile->getBoundBox()))
			threadedBosses->collisionInX(tempTile);
	}
}

void CollisionManager::threadedBossCollisionY()
{
	int i = 0, j = 0;
	for (j = threadedBosses->getPosition().y / TILE_SIZE; j < ((threadedBosses->getPosition().y + threadedBosses->getSize().y) / TILE_SIZE); j++)
	{
		if (!phaseMapManager->isValidTile(threadedBosses->getPosition().x / TILE_SIZE, j))
			continue;
		PhaseMap::Tiles::Tile *tempTile = phaseMapManager->getTile(threadedBosses->getPosition().x / TILE_SIZE, j);
		if (threadedBosses->getBoundBox().intersects(tempTile->getBoundBox()))
			threadedBosses->collisionInY(tempTile);
		else
			threadedBosses->setOnGround(false);
	}
}

void CollisionManager::threadedBossCollisionPlayer()
{
	sf::Time elapsed = clockPlayerAttack.getElapsedTime();

	if (threadedBosses->getBoundBox().intersects(player1->getBoundBox()))
	{
		//checando se o inimigo est?? colidindo com o player
		if (player1->getSpeed().x > 0)
			player1->setPosition({threadedBosses->getBoundBox().left - player1->getBoundBox().width, player1->getPosition().y});
		else if (player1->getSpeed().x < 0 && player1->getSpeed().y > 0.6)
			player1->setPosition({threadedBosses->getBoundBox().left + player1->getBoundBox().width, player1->getPosition().y});
		else if (player1->getSpeed().x < 0)
			player1->setPosition({threadedBosses->getBoundBox().left + player1->getBoundBox().width, player1->getPosition().y});
		player1->setSpeed({0, player1->getSpeed().y});
		threadedBosses->setSpeed({0, threadedBosses->getSpeed().y});

		if (elapsed.asSeconds() >= 1)
		{
			player1->setHp(player1->getHp() - threadedBosses->getAttackDamage());
			clockEnemyAttack.restart();
		}
	}
	else if (player2 != NULL)
		if (!player2->getOnGround() && abs(player1->getPosition().x - threadedBosses->getPosition().x) <= (threadedBosses->getBoundBox().width + 10))
			if (player2->getBoundBox().intersects(threadedBosses->getBoundBox()))
			{
				threadedBosses->setHp(threadedBosses->getHp() - player2->getAttackDamage());
				player2->setOnGround(true);
				player2->setSpeed({player1->getSpeed().x, 0});
				player2->jump();
				clockPlayerAttack.restart();
				clockEnemyAttack.restart();
			}
}

void CollisionManager::setPlayer1(Entidade::Player::Player1 *p1) { player1 = p1; }
void CollisionManager::setPlayer2(Entidade::Player::Player2 *p2) { player2 = p2; }
void CollisionManager::setPhaseMapManager(PhaseMap::Tiles::PhaseMapManager *phaseMapMa) { phaseMapManager = phaseMapMa; }
void CollisionManager::setEnemiesList(Lists::EnemiesList *e) { this->enemiesList = e; }
void CollisionManager::setObstacleList(Lists::ObstacleList *o) { this->obstacleList = o; }
void CollisionManager::setThreadedBoss(Tred::ThreadedBoss *t) { this->threadedBosses = t; }

void CollisionManager::clearAllLists()
{
	if (this->enemiesList != NULL && !this->enemiesList->isEmpty())
		this->enemiesList->setNull();

	if (this->obstacleList != NULL && !this->obstacleList->isEmpty())
		this->obstacleList->setNull();

	this->enemiesList = NULL;
	this->obstacleList = NULL;
}

void CollisionManager::ResetAll()
{
	player1 = NULL;
	player2 = NULL;
	enemiesList = NULL;
	obstacleList = NULL;
}