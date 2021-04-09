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

	public:
		Save();
		~Save();

		void continueSave(); // Classe chamada depois de setar todos os saves
		json continueRestore();

		void setPhasePlayerName(const string player1Name, const string player2Name, const bool multiplayer, const int phaseIs);
		void setPlayer1Save(json jPlayer1);
		void setZombieSave(json jZombie);
		void setPlayer2Save(json jPlayer2);
	};
}
