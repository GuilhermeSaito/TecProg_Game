#pragma once

#include "PhaseMapManager.h"
#include "player1.h"
#include "Player2.h"
#include "CollisionManager.h"

// Just for the defines
#include "menu.h"

#define PHASE1 11
#define PHASE2 12
#define PHASE3 13
#define PHASE4 14

#define PLAYER_DIE 66
#define OPTIONS 70
#define SAVE 50
#define RANK 100

namespace PhaseMap
{
	class PhaseMapGeneral : public Menu
	{
	protected:
		Tiles::PhaseMapManager phaseMapManager;

		Entidade::Player::Player1 *player1;
		Entidade::Player::Player2 *player2;

		Lists::EnemiesList enemiesList;
		Lists::ObstacleList obstacleList;

		sf::View player1View;

		CollisionManager collisionManager;

		// Em vez de ir criando varios Sprite para o background, eu coloco tudo no vector, dai eh soh percorrer e dar um draw
		std::vector<sf::Sprite *> phaseBackGroundSprite;

	public:
		PhaseMapGeneral(sf::RenderWindow *window = NULL, std::string path = "");
		virtual ~PhaseMapGeneral();

		virtual void update(int &controller);
		virtual void render(int &controller);
		bool loadPhaseMap();

	protected:
		void setViewInPlayer1(const int controller);
		void phaseTransition(int &contoller);
		const bool isPlayerDead();
		void enemyKilled();
		const bool isGameClear();

		virtual void placingEnemies();
		virtual void placingObstacles();

		// Soh para evitar possiveis problemas de polimorfismo
		int Start() override { return 0; }

	public:
		void resetEverythingForTransition();

		void setPlayer1(Entidade::Player::Player1 *p1);
		void setPlayer2(Entidade::Player::Player2 *p2);
		void loadListsInCollision();

		Lists::EnemiesList *getEnemiesList();
		Lists::ObstacleList *getObstacleList();

		void ResetAll();
	};
}
