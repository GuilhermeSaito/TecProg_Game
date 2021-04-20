#include "enemyEntity.h"
#include "data.h"
#include "projectile.h"
#include "player1.h"

#define GOBLIN_MAGE 32

#pragma once

namespace Entidade
{
    namespace Enemy
    {
        class GoblinMage: public EnemyEntity
        {
        private:
            sf::Clock clock;
            sf::Time elapsed;

            ListElement<Projectile> projectiles;

        public:
            GoblinMage(sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0);
			~GoblinMage();

            ListElement<Projectile>* getProjectiles();
            void shootProjectile(sf::Vector2f playerPosition);

			void movimentation(sf::Vector2f playerPosition);
			void update(Entidade::Player::Player1* p) override;
            void render(sf::RenderWindow &window) override;

            json getSave() override;
        };
    }
}