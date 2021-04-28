#include "projectile.h"

#include <cmath>

Projectile::Projectile(sf::RenderWindow *window, sf::Vector2f playerPosition, sf::Vector2f enemyPosition, float ls) : Menu(window)
{
  if (!projectileTexture.loadFromFile("src/data/enemy/projectileTexture.png"))
    EXIT_FAILURE;

  //the proejectile's linear speed. It's components on the Y and X axis will vary, given the player's position
  this->linearSpeed = ls;

  //the projectile initial position will always be the enemy position
  this->pos.x = enemyPosition.x + 16;
  this->pos.y = enemyPosition.y + 16;

  //initializing sprite
  this->sprite.setTexture(projectileTexture);
  this->sprite.setTextureRect(sf::IntRect(164, 88, 12, 12));
  this->sprite.setScale(sf::Vector2f(1.5, 1.5));
  this->sprite.setPosition(this->pos.x, this->pos.y);
  this->rect.setSize(sf::Vector2f(12, 12));

  //math made to calculate the speed on the cartesian plane
  this->angle = atan((abs(playerPosition.y - enemyPosition.y)) / (abs(playerPosition.x - enemyPosition.x)));
  this->speed.y = this->linearSpeed * sin(this->angle);
  this->speed.x = this->linearSpeed * cos(this->angle);

  if (playerPosition.y < enemyPosition.y)
    this->speed.y = this->speed.y * (-1);

  if (playerPosition.x < enemyPosition.x)
    this->speed.x = this->speed.x * (-1);
}

Projectile::~Projectile()
{
  window = NULL;
}

sf::FloatRect Projectile::getBoundBox()
{
  return sf::FloatRect(this->pos.x, this->pos.y, rect.getSize().x, rect.getSize().y);
}

void Projectile::update(Entidade::Player::Player1 *p)
{
  this->pos.x += this->speed.x;
  this->pos.y += this->speed.y;
  this->sprite.setPosition(this->pos.x, this->pos.y);
}

void Projectile::render()
{
  window->draw(this->sprite);
}
