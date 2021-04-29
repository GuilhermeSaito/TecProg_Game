#pragma once

#include "player1.h"
#include "Player2.h"
#include "PhaseMapManager.h"
#include "enemiesList.h"
#include "obstacleList.h"

// Esses includes poderiam estar no phaseMapGeneral, pq, parece que soh utiliza os pontos que estao com o #define em cada classe
#include "zombie.h"
#include "goblinMage.h"
#include "flyingEnemy.h"
#include "boss.h"
// Esses 2 aqui sao para utilizar o #define no metodo do dano do objeto no player
#include "spikeTrap.h"
#include "fallStone.h"

#define TILE_SIZE 48

class CollisionManager
{
private:
	Entidade::Player::Player1 *player1;
	Entidade::Player::Player2 *player2;
	PhaseMap::Tiles::PhaseMapManager *phaseMapManager;
	Lists::EnemiesList *enemiesList;
	Lists::ObstacleList *obstacleList;

	sf::Clock clockEnemyAttack;
	sf::Clock clockPlayerAttack;
	sf::Clock spikeTrapAttack1;
	sf::Clock spikeTrapAttack2;

public:
	CollisionManager();
	~CollisionManager();

	void startVerifyCollision();

private:
	void player1CollisionX();
	void player1CollisionY();
	void player2CollisionX();
	void player2CollisionY();
	void enemiesCollisionX();
	void enemiesCollisionY();
	void enemiesProjectiliesCollision();
	void enemyCollidesPlayer();
	void playerCollidesEnemy();
	void obstacleCollidesPlayers();
	void obstacleCollisionY();

public:
	void setPlayer1(Entidade::Player::Player1 *p1);
	void setPlayer2(Entidade::Player::Player2 *p2);
	void setPhaseMapManager(PhaseMap::Tiles::PhaseMapManager *phaseMapMa);
	void setEnemiesList(Lists::EnemiesList *e);
	void setObstacleList(Lists::ObstacleList *o);

	void clearAllLists();

	void ResetAll();
};
