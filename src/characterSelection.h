#pragma once

#include "SwitchPanel.h"
#include "data.h"

#include <iostream>
using std::string;

namespace StartScreen
{
	class CharacterSelection : public SwitchPanel
	{
	private:
		sf::Text menu1;
		sf::Text menu2;
		sf::Text menu3;
		sf::Text menu4;

		string player1Name;
		string player2Name;

		sf::Sprite player1Sprite;
		sf::Sprite player2Sprite;

		bool isMultiplayer;

		// For sprite animation
		sf::Clock clock1;
		sf::Clock clock2;
		int contAnimationPlayer1;
		int contAnimationPlayer2;

	public:
		CharacterSelection();
		~CharacterSelection();

		int Start(sf::RenderWindow &window) override;

	private:
		int characterSelection(sf::RenderWindow &window);
		int nameCharacterSelection(sf::RenderWindow &window); // Esse metodo eh interessante, que eh o input dos nomes dos player, nao sei se essa eh a melhor forma de se fazer, mas funciona hahaha

		void updateMenuCollor(int controller, sf::RenderWindow &window);
		void player1Animation();
		void player2Animation();

		void player1NameEnter(int &totalChar1, sf::Event &event);
		void player2NameEnter(int &totalChar2, sf::Event &event);

	public:
		void setPlayer1Name(const string name1);
		const string getPlayer1Name() const;
		void setPlayer2Name(const string name2);
		const string getPlayer2Name() const;
		void setIsMultiplayer(const bool multiplayer);
		const bool getIsMultiplayer() const;

		int notImplementedYet(sf::RenderWindow &window);
	};
}
