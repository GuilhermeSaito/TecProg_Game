#pragma once

#include "shooterEntity.h"

#define BOSS 34
#define BOSS_POINTS 70

namespace Entidade
{
    namespace Enemy
    {
        class Boss : public ShooterEntity
        {
        private:
            sf::Texture bossTexture;

        public:
            Boss(sf::RenderWindow *window = NULL, sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0, const int point = 0);
            ~Boss();

            void shootProjectile(sf::Vector2f playerPosition) override;

            void movimentation(sf::Vector2f playerPosition) override;
            void update(Entidade::Player::Player1 *p) override;
            void render() override;

            json getSave() override;
        };
    }
}