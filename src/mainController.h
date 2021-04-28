#pragma once

#include "menu.h"
#include "splashScreen.h"
#include "openMenu.h"
#include "phaseSelection.h"
#include "characterSelection.h"
#include "rankingScreen.h"
#include "playerDieScreen.h"
#include "phaseManager.h"

#include <vector>

/*
	Essa eh a entrada da aplicacao, chamada no int main(). 
	Para trocar de telas, entre a splashScreen -> CharacterSelection -> ...
		Eh feita pelo switcher.
*/

class MainController
{
private:
	sf::RenderWindow window;
	std::vector<Menu *> switcher; // Responsavel por armazenar as instancias dos objetos e trocar de telas quando necessario.

	Screen::SplashScreen splashScreen;
	StartScreen::OpenMenu openMenu;
	StartScreen::PhaseSelection phaseSelection;
	StartScreen::CharacterSelection characterSelection;
	Screen::RankingScreen rankingScreen;
	Screen::PlayerDieScreen playerDieScreen;
	PhaseMap::PhaseManager phaseManager;

public:
	MainController();
	~MainController();

	void Start();
};
