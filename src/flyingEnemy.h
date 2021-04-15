#include "enemyEntity.h"
#include "data.h"
#include "listManager.h"
#include "projectile.h"
#include "player1.h"

#pragma once

namespace Entidade
{
    namespace Enemy
    {
        class FlyingEnemy: public EnemyEntity
        {
        private:
            sf::Clock clock;
            sf::Time elapsed;
            //the following atributes will be used for the wave aquation on the Y axis.
            float originalYposition;

            ListElement<Projectile> projectiles;

        public:
            FlyingEnemy(sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0);
			~FlyingEnemy();


            ListElement<Projectile>* getProjectiles();
            void shootProjectile();

			void movimentation(sf::Vector2f playerPosition);
			void update(Entidade::Player::Player1* p);
            void render(sf::RenderWindow &window);
        };
    }
}