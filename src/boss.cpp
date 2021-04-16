#include "boss.h"

using namespace Entidade::Enemy;

Boss::Boss(sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage) :
	  EnemyEntity(pos, spee, hP, attackDamage),
    projectiles(),
    clock()
{
  this->walkSpeed = spee.x;

  rect.setSize(sf::Vector2f(2*87.f, 2*96.f));
  rect.setPosition(pos);

  sprite.setTexture(*(Data::getInstance()->getBossTexture()));
  sprite.setTextureRect(sf::IntRect(0, 0, 87, 96));
  sprite.setScale({2.f, 2.f});
  sprite.setPosition(rect.getPosition());

  healthBar.setFillColor(sf::Color::Red);
  healthBar.setPosition(sf::Vector2f(position.x - 10, position.y - 25));
}
Boss::~Boss()
{
  this->projectiles.setNull();
}

ListElement<Projectile>* Boss::getProjectiles()
{
  return &this->projectiles;
}

void Boss::shootProjectile(sf::Vector2f playerPosition)
{
    if (!this->projectiles.isEmpty())
        this->projectiles.setNull();

    this->projectiles.include(new Projectile({playerPosition.x, playerPosition.y}, this->position, 10.f));
    this->projectiles.include(new Projectile({playerPosition.x, playerPosition.y-50}, this->position, 10.f));
    this->projectiles.include(new Projectile({playerPosition.x, playerPosition.y+50}, this->position, 10.f));
}

void Boss::movimentation(sf::Vector2f playerPosition)
{
  gravity();

  if (playerPosition.x < this->position.x)
  {
    this->speed.x = this->walkSpeed;
    this->position.x -= this->speed.x;
    sprite.setTexture(*(Data::getInstance()->getBossTexture()));
    sprite.setTextureRect(sf::IntRect(0, 0, 87, 96));
    sprite.setScale({2.f, 2.f});
  }

  else if (playerPosition.x > this->position.x)
  {
    this->speed.x = this->walkSpeed;
    this->position.x +=this->speed.x;
    sprite.setTexture(*(Data::getInstance()->getBossTexture()));
    sprite.setTextureRect(sf::IntRect(4, 96, 87, 96));
    sprite.setScale({2.f, 2.f});
  }

  else
  {
  }

  this->rect.setPosition(position);
  this->sprite.setPosition(position);
}

void Boss::update(Entidade::Player::Player1* p)
{
  healthBar.setSize(sf::Vector2f(hp, 5.f));
  healthBar.setPosition(sprite.getPosition().x - 10, sprite.getPosition().y - 20);
  movimentation(p->getPosition());

  this->elapsed = this->clock.getElapsedTime();
  if (this->elapsed.asSeconds() >= 3.5)
  {
    shootProjectile(p->getPosition());
    clock.restart();
  }

  if (!this->projectiles.isEmpty())
    projectiles.update(p);
}

void Boss::render(sf::RenderWindow& window)
{
	window.draw(healthBar);
	window.draw(sprite);

  projectiles.render(window);
}

json Boss::getSave()
{
  json j = json::object();

  j["boss"]["positionX"] = position.x;
  j["boss"]["positionY"] = position.y;

  return j;
}