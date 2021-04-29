#include "enemyEntity.h"

using namespace Entidade;

EnemyEntity::EnemyEntity(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f spee, float hp, float attack, const int point) : Entity(window, pos, spee, hp, attack, point),
																																   canHitPlayer1(true),
																																   canHitPlayer2(true),
																																   isDead(false),
																																   hasProjectiles(false),
																																   witchTypeOfTrap(0)
{
}
EnemyEntity::~EnemyEntity()
{
	window = NULL;
}

void EnemyEntity::timerCanHitPlayer()
{
}
const bool EnemyEntity::getCanHitPlayer1() const { return canHitPlayer1; }
const bool EnemyEntity::getCanHitPlayer2() const { return canHitPlayer2; }

const bool EnemyEntity::getHasProjectiles() const { return hasProjectiles; }
void EnemyEntity::setHasProjectiles(const bool y) { hasProjectiles = y; }

void EnemyEntity::setWitchTypeOfTrap(const int w) { witchTypeOfTrap = w; }
const int EnemyEntity::getWitchTypeOfTrahp() const { return witchTypeOfTrap; }