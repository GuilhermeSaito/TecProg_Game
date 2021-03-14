#pragma once

#include "player1.h"
#include "Player2.h"
#include "PhaseMapManager.h"

#define TILE_SIZE 48

class CollisionManager
{
private:
	Entidade::Player::Player1* player1;
	Entidade::Player::Player2* player2;
	PhaseMap::Tiles::PhaseMapManager* phaseMapManager;

public:
	CollisionManager();
	~CollisionManager();

	void startVerifyCollision();

private:
	void player1CollisionX();
	void player1CollisionY();
	void player2CollisionX();
	void player2CollisionY();

public:
	void setPlayer1(Entidade::Player::Player1* p1);
	void setPlayer2(Entidade::Player::Player2* p2);
	void setPhaseMapManager(PhaseMap::Tiles::PhaseMapManager* phaseMapMa);

	void ResetAll();
};

