#pragma once

#include "enemyEntity.h"

#define FALL_STONE -4
#define FALL_STONE_POINTS 400

namespace Entidade
{
    namespace Obstacle
    {
        class FallStone : public EnemyEntity
        {
        private:
            sf::Texture fallStoneTexture;

        public:
            FallStone(sf::RenderWindow *window = NULL, sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0, const int point = 0);
            ~FallStone();

            virtual void update(Entidade::Player::Player1 *p) override;
            virtual void render() override;

            virtual json getSave() override;

        private:
        void movimentation(sf::Vector2f playerPosition) override;
            Lists::ProjectilesList *getProjectiles() override;
        };
    }
}