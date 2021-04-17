#pragma once

#include "PhaseMapManager.h"
#include "player1.h"
#include "Player2.h"
#include "CollisionManager.h"

// Just for the defines
#include "SwitchPanel.h"

#define PHASE1 11
#define PHASE2 12
#define PHASE3 13
#define PHASE4 14

#define PLAYER_DIE 66
#define OPTIONS 70
#define SAVE 50

namespace PhaseMap
{
	class PhaseMapGeneral
	{
	protected:
		Tiles::PhaseMapManager phaseMapManager;

		Entidade::Player::Player1 *player1;
		Entidade::Player::Player2 *player2;

		sf::View player1View;

		CollisionManager collisionManager;

		// Em vez de ir criando varios Sprite para o background, eu coloco tudo no vector, dai eh soh percorrer e dar um draw
		std::vector<sf::Sprite *> phaseBackGroundSprite;

	public:
		PhaseMapGeneral(std::string path = "");
		virtual ~PhaseMapGeneral();

		virtual void update(int &controller);
		virtual void render(sf::RenderWindow &window, int &controller);
		bool loadPhaseMap();

	protected:
		void setViewInPlayer1(sf::RenderWindow &window, const int controller);
		void phaseTransition(int &contoller);
		bool isPlayerDead();

	public:
		void resetEverythingForTransition();

		void setPlayer1(Entidade::Player::Player1 *p1);
		void setPlayer2(Entidade::Player::Player2 *p2);

		void ResetAll();
	};
}
