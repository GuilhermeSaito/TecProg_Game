#include "goblinMage.h"

using namespace Entidade::Enemy;

GoblinMage::GoblinMage(sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage) :
	EnemyEntity(pos, spee, hP, attackDamage)
{
  this->walkSpeed = spee.x;

  rect.setSize(sf::Vector2f(33.f, 45.f));
	rect.setPosition(pos);

	sprite.setTexture(*(Data::getInstance()->getGoblinMageTexture()));
	sprite.setTextureRect(sf::IntRect(0, 0, 33, 45));
	sprite.setPosition(rect.getPosition());

	healthBar.setFillColor(sf::Color::Red);
	// Apagar esse setPosition do healthBar, pois ele vai ficar atualizando quando o inimigo se mover
	healthBar.setPosition(sf::Vector2f(position.x - 10, position.y - 25));
}
GoblinMage::~GoblinMage()
{
}

void GoblinMage::movimentation(float posx)
{
  gravity();

  if (posx <= this->position.x)
  {
    this->speed.x = this->walkSpeed;
    this->position.x -= this->speed.x;
    sprite.setTexture(*(Data::getInstance()->getGoblinMageTexture()));
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 47));
  }

  else if (posx > this->position.x)
  {
    this->speed.x = this->walkSpeed;
    this->position.x +=this->speed.x;
    sprite.setTexture(*(Data::getInstance()->getGoblinMageTexture()));
    sprite.setTextureRect(sf::IntRect(2, 49, 32, 47));
  }

  else
  {
  }

  this->rect.setPosition(position);
  this->sprite.setPosition(position);
}

void GoblinMage::update(float posx)
{
  healthBar.setSize(sf::Vector2f(hp, 5.f));
  healthBar.setPosition(sprite.getPosition().x - 10, sprite.getPosition().y - 20);
  movimentation(posx);
}