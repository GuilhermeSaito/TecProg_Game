#pragma once

#include <SFML/Graphics.hpp>

// Em vez de ficar usando numeros, coloquei com nomes.	Acredito que daria para usar um Enum aqui...
#define EXIT_GAME -1
#define SPLASH_SCREEN 0
#define OPEN_MENU 1
#define PHASE_SELECTION 2
#define CHARACTER_SELECTION 3
#define RANKING_SCREEN 4
#define PLAYER_DIE_SCREEN 5
#define PHASE_MANAGER 6

#define PHASE1 11
#define PHASE2 12
#define PHASE3 13
#define PHASE4 14

class Menu
{
protected:
	sf::RenderWindow *window;

public:
	Menu(sf::RenderWindow *window);
	virtual ~Menu();

	virtual int Start() = 0;
};