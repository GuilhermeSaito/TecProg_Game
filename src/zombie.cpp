#include "zombie.h"

using namespace Entidade::Enemy;

Zombie::Zombie(sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage) :
	EnemyEntity(pos, spee, hP, attackDamage)
{
  this->walkSpeed = spee.x;

  rect.setSize(sf::Vector2f(32.f, 47.f));
	rect.setPosition(pos);

	sprite.setTexture(*(Data::getInstance()->getZombieTexture()));
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 47));
	sprite.setPosition(rect.getPosition());

	healthBar.setFillColor(sf::Color::Red);
	// Apagar esse setPosition do healthBar, pois ele vai ficar atualizando quando o inimigo se mover
	healthBar.setPosition(sf::Vector2f(position.x - 10, position.y - 25));
}
Zombie::~Zombie()
{
}

void Zombie::movimentation(float posx)
{
  gravity();

  if (posx <= this->position.x)
  {
    this->speed.x = this->walkSpeed;
    this->position.x -= this->speed.x;
    sprite.setTexture(*(Data::getInstance()->getZombieTexture()));
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 47));
  }

  else if (posx > this->position.x)
  {
    this->speed.x = this->walkSpeed;
    this->position.x +=this->speed.x;
    sprite.setTexture(*(Data::getInstance()->getZombieTexture()));
    sprite.setTextureRect(sf::IntRect(2, 50, 32, 47));
  }

  else
  {
  }

  this->rect.setPosition(position);
  this->sprite.setPosition(position);
}

void Zombie::update(float posx)
{
  healthBar.setSize(sf::Vector2f(hp, 5.f));
  healthBar.setPosition(sprite.getPosition().x - 10, sprite.getPosition().y - 20);
  movimentation(posx);
}