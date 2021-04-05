#include "enemyEntity.h"
#include "data.h"

#pragma once

namespace Entidade
{
    namespace Enemy
    {
        class GoblinMage: public EnemyEntity
        {
        private:


        public:
            GoblinMage(sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0);
			~GoblinMage();

			void movimentation(float posx);
			void update(float posx);
        };
    }
}