#pragma once

#include "player1.h"
#include "Player2.h"
#include "PhaseMapManager.h"
#include "listManager.h"
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
	ListElement<Entidade::Enemy::Zombie>* zombiesList;
	ListElement<Entidade::Enemy::GoblinMage>* goblinMagesList;
	ListElement<Entidade::Enemy::FlyingEnemy>* flyingEnemiesList;
	Entidade::Enemy::Boss* boss;

public:
	CollisionManager();
	~CollisionManager();

	void startVerifyCollision();

private:
	void player1CollisionX();
	void player1CollisionY();
	void player2CollisionX();
	void player2CollisionY();
	void zombiesCollisionX();
	void zombiesCollisionY();
	void goblinMagesCollisionX();
	void goblinMagesCollisionY();
	void goblinMagesProjectiliesCollision();
	void flyingEnemiesCollisionX();
	void flyingEnemiesCollisionY();
	void flyingEnemiesProjectilesCollision();
	void bossCollisionX();
	void bossCollisionY();
	void bossProjectilesCollision();

public:
	void setPlayer1(Entidade::Player::Player1* p1);
	void setPlayer2(Entidade::Player::Player2* p2);
	void setPhaseMapManager(PhaseMap::Tiles::PhaseMapManager* phaseMapMa);
	void setZombieList(ListElement<Entidade::Enemy::Zombie>* l);
	void setGoblinMageList(ListElement<Entidade::Enemy::GoblinMage>* l);
	void setFlyingEnemiesList(ListElement<Entidade::Enemy::FlyingEnemy>* l);
	void setBoss(Entidade::Enemy::Boss* b);
	void clearAllLists();

	void ResetAll();
};

