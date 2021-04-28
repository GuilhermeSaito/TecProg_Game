#pragma once

#include "menu.h"

/*
	Classe para selecionar a phase que o jogador deseja jogar, soh podera ser escolhida no inicio, depois para passar de fase
		sera necessario chegar ateh o final da fase, NAO EH POSSIVEL VOLTAR DE FASE, soh avancar
*/
namespace StartScreen
{
	class PhaseSelection : public Menu
	{
	private:
		sf::Text menu1;
		sf::Text menu2;
		sf::Text menu3;
		sf::Text menu4;

		// Just to show the player how is the phase
		sf::Sprite beginnerPhaseSprite;
		sf::Sprite blueOceanPhaseSprite;
		sf::Sprite cavePhaseSprite;
		sf::Sprite deathPhaseSprite;

		int witchPhaseIs;

		sf::Texture beginnerPhaseBackGround;
		sf::Texture blueOceanPhaseBackGround;
		sf::Texture cavePhaseBackGround;
		sf::Texture deathPhaseBackGround;
		sf::Font openMenufont;

	public:
		PhaseSelection(sf::RenderWindow *window = NULL);
		~PhaseSelection();

		int Start() override;

	private:
		int phaseSelection();

		void updateMenuCollor(int controller);

	public:
		void setWitchPhaseIs(const int phaseIs);
		const int getWitchPhaseIs() const;
	};
}