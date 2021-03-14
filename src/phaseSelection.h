#pragma once

#include "SwitchPanel.h"
#include "data.h"

/*
	Classe para selecionar a phase que o jogador deseja jogar, soh podera ser escolhida no inicio, depois para passar de fase
		sera necessario chegar ateh o final da fase, NAO EH POSSIVEL VOLTAR DE FASE, soh avancar
*/
namespace StartScreen
{
	class PhaseSelection : public SwitchPanel
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
	
	public:
		PhaseSelection();
		~PhaseSelection();

		int Start(sf::RenderWindow& window) override;

	private:
		int phaseSelection(sf::RenderWindow& window);

		void updateMenuCollor(int controller, sf::RenderWindow& window);

	public:
		void setWitchPhaseIs(const int phaseIs);
		const int getWitchPhaseIs() const;
	};
}