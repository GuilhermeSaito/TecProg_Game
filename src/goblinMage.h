#pragma once

#include "enemyEntity.h"

#include "projectilesList.h"
#include "player1.h"

#define GOBLIN_MAGE 32
#define GOBLIN_MAGE_POINTS 40

namespace Entidade
{
    namespace Enemy
    {
        class GoblinMage : public EnemyEntity
        {
        private:
            sf::Clock clock;
            sf::Time elapsed;

            Lists::ProjectilesList projectiles;

            sf::Texture goblinMageTexture;

        public:
            GoblinMage(sf::RenderWindow *window = NULL, sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0, const int point = 0);
            ~GoblinMage();

            Lists::ProjectilesList *getProjectiles();
            void shootProjectile(sf::Vector2f playerPosition);

            void movimentation(sf::Vector2f playerPosition);
            void update(Entidade::Player::Player1 *p) override;
            void render() override;

            json getSave() override;
        };
    }
}