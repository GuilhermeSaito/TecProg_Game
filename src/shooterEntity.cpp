#include "shooterEntity.h"

using namespace Entidade;

ShooterEntity::ShooterEntity(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage, const int point) : EnemyEntity(window, pos, spee, hP, attackDamage, point),
                                                                                                                                             projectiles(),
                                                                                                                                             clock()
{
}
ShooterEntity::~ShooterEntity()
{
    window = NULL;
    this->projectiles.setNull();
}

Lists::ProjectilesList *ShooterEntity::getProjectiles()
{
    return &this->projectiles;
}