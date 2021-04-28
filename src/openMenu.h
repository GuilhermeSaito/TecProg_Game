#pragma once

#include "menu.h"

#include "save.h"

/*
	� Essa eh a tela do carinha com a montanha, tudo pixelado.
	� Classe que pega o save do jogador: Na fase (as posicoes dos player, inimigos, score, hp, etc), e quando mata o boss para mostrar o ranking
	� O save eh pego pela classe Save, no namespace SaveGame. O save estah armazenado no formato json na pasta "saveFile"
	
	� Caso o jogador deseje continuar onde parou, essa classe retorna o PHASE_MANAGER para o mainController, e deixa carregado, nessa classe mesmo
		o save no jSave que eh passada para o PhaseManager, para assim arrumar as posicoes, scores, hp, etc.
*/
namespace StartScreen
{
	class OpenMenu : public Menu
	{
	private:
		sf::Sprite backGroundSprite;

		sf::Text menu1;
		sf::Text menu2;
		sf::Text menu3;
		sf::Text menu4;

		SaveGame::Save save;
		json jSave;

		sf::Texture openMenuBackGround;
		sf::Font openMenufont;

	public:
		OpenMenu(sf::RenderWindow *window);
		~OpenMenu();

		int Start() override;

	private:
		void updateMenuCollor(int controller);

	public:
		json getContinueSave();
	};
}