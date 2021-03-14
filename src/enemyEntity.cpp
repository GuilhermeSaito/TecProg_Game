#include "enemyEntity.h"

using namespace Entidade;

EnemyEntity::EnemyEntity(sf::Vector2f pos, sf::Vector2f spee, float hp, float attack):
	Entity(pos, spee, hp, attack),
	canHitPlayer1(true),
	canHitPlayer2(true),
	isDead(false)
{
}
EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::timerCanHitPlayer()
{}
const bool EnemyEntity::getCanHitPlayer1() const { return canHitPlayer1; }
const bool EnemyEntity::getCanHitPlayer2() const { return canHitPlayer2; }

const bool EnemyEntity::getIsDead() const { return isDead; }
void EnemyEntity::setIsDead(const bool dead) { isDead = dead; }

void EnemyEntity::render(sf::RenderWindow& window)
{
	window.draw(healthBar);
	window.draw(sprite);
}