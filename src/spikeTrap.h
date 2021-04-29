#pragma once

#include "enemyEntity.h"

#define SPIKE_TRAP -3
#define SPIKE_TRAP_POINTS 150

namespace Entidade
{
    namespace Obstacle
    {
        class SpikeTrap : public EnemyEntity
        {
        private:
            sf::Texture spikeTrapTexture;

        public:
            SpikeTrap(sf::RenderWindow *window = NULL, sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0, const int point = 0);
            ~SpikeTrap();

            virtual void update(Entidade::Player::Player1 *p) override;
            virtual void render() override;

            virtual json getSave() override;

        private:
            void movimentation(sf::Vector2f playerPosition) override;
            Lists::ProjectilesList *getProjectiles() override;
        };
    }
}