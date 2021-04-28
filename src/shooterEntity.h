#pragma once

#include "enemyEntity.h"
#include "projectile.h"
#include "player1.h"

namespace Entidade
{
    class ShooterEntity : public EnemyEntity
    {
    protected:
        sf::Clock clock;
        sf::Time elapsed;

        Lists::ProjectilesList projectiles;

    public:
        ShooterEntity(sf::RenderWindow *window = NULL, sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0, const int point = 0);
        virtual ~ShooterEntity();

        Lists::ProjectilesList *getProjectiles();
        virtual void shootProjectile(sf::Vector2f playerPosition) = 0;

        virtual void movimentation(sf::Vector2f playerPosition) = 0;
        virtual void update(Entidade::Player::Player1 *p) = 0;
        virtual void render() = 0;

        virtual json getSave() = 0;
    };
}