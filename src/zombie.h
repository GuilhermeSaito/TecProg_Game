#pragma once

#include "enemyEntity.h"
#include "data.h"

namespace Entidade
{
	namespace Enemy
	{
		class Zombie : public EnemyEntity
		{
		public:
			Zombie(sf::Vector2f pos = { 2 * 48, 27 * 48 }, sf::Vector2f spee = { 0, 0 }, float hP = 100, float attackDamage = 15);
			~Zombie();
		};
	}
}
