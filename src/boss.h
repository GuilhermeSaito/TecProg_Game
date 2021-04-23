#include "enemyEntity.h"
#include "data.h"
#include "projectile.h"
#include "player1.h"

#define BOSS 34

#pragma once

namespace Entidade
{
    namespace Enemy
    {
        class Boss: public EnemyEntity
        {
        private:
            sf::Clock clock;
            sf::Time elapsed;
            
            ProjectilesList projectiles;

        public:
            Boss(sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0);
			~Boss();

            ProjectilesList* getProjectiles();
            void shootProjectile(sf::Vector2f playerPosition);

			void movimentation(sf::Vector2f playerPosition);
			void update(Entidade::Player::Player1* p) override;
            void render(sf::RenderWindow &window) override;

            json getSave() override;
        };
    }
}