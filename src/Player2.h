#pragma once

#include "entity.h"

namespace Entidade
{
	namespace Player
	{
		class Player2 : public Entity
		{
		private:
			sf::Clock clock;
			sf::Time elapsed;
			int contAnimation;

		public:
			Player2(sf::Vector2f pos = { 2 * 48, 27 * 48 }, sf::Vector2f spee = { 0, 0 }, float hP = 100, float attackDamage = 40.5);
			~Player2();

			void movementation();
			// Qualquer coisa, esse metodo da para tronar ele virtual na Entity e ficar dando override nas classes derivadas.
			void draw(sf::RenderWindow& window);

		private:
			void spriteAnimation();
			void updateContAnimation();
		};
	}
}
