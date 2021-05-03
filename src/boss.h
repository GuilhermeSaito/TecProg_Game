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
        protected:
            sf::Texture bossTexture;
            sf::Clock clockJump;

        public:
            Boss(sf::RenderWindow *window = NULL, sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0, const int point = 0);
            ~Boss();

            void shootProjectile(sf::Vector2f playerPosition) override;

            void movimentation(sf::Vector2f playerPosition) override;
            void update(Entidade::Player::Player1 *p) override;
            void render() override;

            json getSave() override;

        private:
            // Isso aqui vai ter um bug, pq no map tem um negocio que o boss pula por normal, enfim :v
            void jumpToAttack(Entidade::Player::Player1 *p1);
        };
    }
}