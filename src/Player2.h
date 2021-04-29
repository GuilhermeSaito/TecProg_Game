#pragma once

#include "player1.h"

namespace Entidade
{
	namespace Player
	{
		class Player2 : public Player1
		{
		private:
			sf::Texture player2Image;

		public:
			Player2(sf::RenderWindow *window = NULL, sf::Vector2f pos = {2 * 48, 27 * 48}, sf::Vector2f spee = {0, 0}, float hP = 100, float attackDamage = 40.5, const int point = 0);
			~Player2();

			void movementation() override;
			// Qualquer coisa, esse metodo da para tronar ele virtual na Entity e ficar dando override nas classes derivadas.
			void draw() override;

			json getSave() override;
		};
	}
}
