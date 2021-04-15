#pragma once

#include "enemyEntity.h"
#include "data.h"
#include "player1.h"

namespace Entidade
{
	namespace Enemy
	{
		class Zombie : public EnemyEntity
		{
		public:
			Zombie(sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0);
			~Zombie();

			void movimentation(sf::Vector2f playerPosition);
			void update(Entidade::Player::Player1* p);

			json getSave() override;
		};
	}
}
