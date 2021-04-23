#include "enemyEntity.h"
#include "data.h"
#include "projectile.h"
#include "player1.h"

#define FLYING_ENEMY 33

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

            ProjectilesList projectiles;

        public:
            FlyingEnemy(sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0);
			~FlyingEnemy();


            ProjectilesList* getProjectiles();
            void shootProjectile();

			void movimentation(sf::Vector2f playerPosition);
			void update(Entidade::Player::Player1* p) override;
            void render(sf::RenderWindow &window) override;

            json getSave() override;
        };
    }
}