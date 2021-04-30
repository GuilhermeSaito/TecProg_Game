#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
using std::string;

#include "nlohmann/json.hpp"
using json = nlohmann::json;

namespace SaveGame
{
	class Save
	{
	private:
		json jArray = json::array();
		json jArrayEnemies = json::array();

	public:
		Save();
		~Save();

		void continueSave(); // Classe chamada depois de setar todos os saves
		json continueRestore();

		void rankingSave(const string player1Name, const string player2Name, const int score, const bool isMultiplayer);
		json rankingRecover();

		void setPhasePlayerName(const string player1Name, const string player2Name, const bool multiplayer, const int phaseIs);
		void setPlayer1Save(json jPlayer1);
		void setEnemiesSave(json jZombie);
		void setPlayer2Save(json jPlayer2);

		void clearJson();

	private:
		const bool isFileEmpty(std::ifstream &in);
	};
}
