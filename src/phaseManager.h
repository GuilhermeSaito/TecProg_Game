#pragma once

#include "phaseMap1.h"
#include "phaseMap2.h"
#include "phaseMap3.h"
#include "phaseMap4.h"
#include "player1.h"
#include "Player2.h"
#include "save.h"

// o include do menu.h estah no PhaseMapManager

namespace PhaseMap
{
	class PhaseManager : public Menu
	{
	private:
		PhaseMap1 phaseMap1;
		PhaseMap2 phaseMap2;
		PhaseMap3 phaseMap3;
		PhaseMap4 phaseMap4;

		Entidade::Player::Player1 player1;
		Entidade::Player::Player2 player2;

		Lists::EnemiesList *enemiesList;

		SaveGame::Save save;

		string player1Name;
		string player2Name;
		bool isMultiplayer;

		bool needToLoadPhase;

		int controller;

		sf::Font openMenufont;

	public:
		PhaseManager(sf::RenderWindow *window = NULL);
		~PhaseManager();

		int Start(json jContinueSave, const string player1Name = "", const string player2Name = "", const bool multiplayer = false, const int phaseIs = PHASE1);

	private:
		int loadPhaseMap(const bool multiplayer);

		void normalizeView();
		void showOptions(int &phase);

		const int loadState(json j);
		void saveState();

		void ResetALL();

		int Start() override { return 0; }
	};
}