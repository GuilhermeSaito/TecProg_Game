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
	public:
		Save();
		~Save();

		void continueSave(const string player1Name, const string player2Name, const bool multiplayer, const int phaseIs, sf::Vector2f player1Location, sf::Vector2f player2Location);
		json continueRestore();
	};
}
