#pragma once

#include "player1.h"
#include "Player2.h"
#include "PhaseMapManager.h"
#include "listManager.h"
#include "zombie.h"
#include "goblinMage.h"

#define TILE_SIZE 48

class CollisionManager
{
private:
	Entidade::Player::Player1* player1;
	Entidade::Player::Player2* player2;
	PhaseMap::Tiles::PhaseMapManager* phaseMapManager;
	ListElement<Entidade::Enemy::Zombie>* zombiesList;
	ListElement<Entidade::Enemy::GoblinMage>* goblinMagesList;

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

public:
	void setPlayer1(Entidade::Player::Player1* p1);
	void setPlayer2(Entidade::Player::Player2* p2);
	void setPhaseMapManager(PhaseMap::Tiles::PhaseMapManager* phaseMapMa);
	void setZombieList(ListElement<Entidade::Enemy::Zombie>* l);
	void setGoblinMageList(ListElement<Entidade::Enemy::GoblinMage>* l);
	void clearAllLists();

	void ResetAll();
};

