#pragma once

#include "player1.h"
#include "Player2.h"
#include "PhaseMapManager.h"
#include "enemiesList.h"
#include "zombie.h"
#include "goblinMage.h"
#include "flyingEnemy.h"
#include "boss.h"

#define TILE_SIZE 48

class CollisionManager
{
private:
	Entidade::Player::Player1* player1;
	Entidade::Player::Player2* player2;
	PhaseMap::Tiles::PhaseMapManager* phaseMapManager;
	EnemiesList* enemiesList;

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

public:
	void setPlayer1(Entidade::Player::Player1* p1);
	void setPlayer2(Entidade::Player::Player2* p2);
	void setPhaseMapManager(PhaseMap::Tiles::PhaseMapManager* phaseMapMa);
	void setEnemiesList(EnemiesList* e);
	void clearAllLists();

	void ResetAll();
};

