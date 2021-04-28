#pragma once

#include "enemyEntity.h"

#include "projectile.h"
#include "player1.h"

#define FLYING_ENEMY 33
#define FLYING_ENEMY_POINTS 50

namespace Entidade
{
    namespace Enemy
    {
        class FlyingEnemy : public EnemyEntity
        {
        private:
            sf::Clock clock;
            sf::Time elapsed;
            //the following atributes will be used for the wave aquation on the Y axis.
            float originalYposition;

            Lists::ProjectilesList projectiles;

            sf::Texture flyingEnemyTexture;

        public:
            FlyingEnemy(sf::RenderWindow *window = NULL, sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0, const int point = 0);
            ~FlyingEnemy();

            Lists::ProjectilesList *getProjectiles();
            void shootProjectile();

            void movimentation(sf::Vector2f playerPosition);
            void update(Entidade::Player::Player1 *p) override;
            void render() override;

            json getSave() override;
        };
    }
}