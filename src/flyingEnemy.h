#pragma once

#include "shooterEntity.h"

#define FLYING_ENEMY 33
#define FLYING_ENEMY_POINTS 50

namespace Entidade
{
    namespace Enemy
    {
        class FlyingEnemy : public ShooterEntity
        {
        private:
            //the following atributes will be used for the wave aquation on the Y axis.
            float originalYposition;

            sf::Texture flyingEnemyTexture;

        public:
            FlyingEnemy(sf::RenderWindow *window = NULL, sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0, const int point = 0);
            ~FlyingEnemy();

            // Esse metodo soh tem esse parametro para dar um override da classe base, NAO EH UTILIZADO o playerPosition
            void shootProjectile(sf::Vector2f playerPosition) override;

            void movimentation(sf::Vector2f playerPosition) override;
            void update(Entidade::Player::Player1 *p) override;
            void render() override;

            json getSave() override;
        };
    }
}