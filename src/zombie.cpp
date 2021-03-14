#include "zombie.h"

using namespace Entidade::Enemy;

Zombie::Zombie(sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage) :
	EnemyEntity(pos, spee, hP, attackDamage)
{
	rect.setPosition(pos);

	sprite.setTexture(*(Data::getInstance()->getZombieTexture()));
	sprite.setPosition(rect.getPosition());

	healthBar.setFillColor(sf::Color::Red);
	// Apagar esse setPosition do healthBar, pois ele vai ficar atualizando quando o inimigo se mover
	healthBar.setPosition(sf::Vector2f(position.x - 10, position.y - 25));
}
Zombie::~Zombie()
{
}