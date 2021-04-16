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
        class Boss: public EnemyEntity
        {
        private:
            sf::Clock clock;
            sf::Time elapsed;
            
            ListElement<Projectile> projectiles;

        public:
            Boss(sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0);
			~Boss();

            ListElement<Projectile>* getProjectiles();
            void shootProjectile(sf::Vector2f playerPosition);

			void movimentation(sf::Vector2f playerPosition);
			void update(Entidade::Player::Player1* p);
            void render(sf::RenderWindow &window);

            json getSave() override;
        };
    }
}