#pragma once

#include "entity.h"

namespace Entidade
{
	namespace Player
	{
		class Player1 : public Entity
		{
		private:
			sf::Clock clock;
			sf::Time elapsed;
			int contAnimation;

			int score;
			sf::Text textScore;
			// Esse ponteiro vai apontar para o view que estah no phaseMapGeneral, serve para colocar certinho o score na tela
			sf::View *player1View;

		public:
			Player1(sf::RenderWindow *window = NULL, sf::Vector2f pos = {2 * 48, 27 * 48}, sf::Vector2f spee = {0, 0}, float hP = 100, float attackDamage = 30, const int point = 0);
			~Player1();

			void movementation();
			// Qualquer coisa, esse metodo da para tronar ele virtual na Entity e ficar dando override nas classes derivadas.
			void draw();
			void setPlayer1View(sf::View *player1View);

			void setScore(const int s);
			const int getScore() const;
			// Metodo a ser chamado para quando algum dos player matar o inimigo
			void updateScore(const int somaPontos);

			json getSave() override;

		private:
			void spriteAnimation();
			void updateContAnimation();
		};
	}
}
