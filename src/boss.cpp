#include "boss.h"

// Usando o abs
#include <math.h>

using namespace Entidade::Enemy;

Boss::Boss(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage, const int point) : ShooterEntity(window, pos, spee, hP, attackDamage, point)
{
  if (!bossTexture.loadFromFile("src/data/enemy/bossTexture.png"))
    EXIT_FAILURE;

  this->hasProjectiles = true;
  this->walkSpeed = spee.x;

  rect.setSize(sf::Vector2f(2 * 87.f, 2 * 96.f));
  rect.setPosition(pos);

  sprite.setTexture(bossTexture);
  sprite.setTextureRect(sf::IntRect(0, 0, 87, 96));
  sprite.setScale({2.f, 2.f});
  sprite.setPosition(rect.getPosition());

  healthBar.setFillColor(sf::Color::Red);
  healthBar.setPosition(sf::Vector2f(position.x - 10, position.y - 25));
}
Boss::~Boss()
{
  window = NULL;
}

void Boss::shootProjectile(sf::Vector2f playerPosition)
{
  if (!this->projectiles.isEmpty())
    this->projectiles.setNull();

  this->projectiles.include(new Projectile(window, {playerPosition.x, playerPosition.y}, this->position, 10.f));
  this->projectiles.include(new Projectile(window, {playerPosition.x, playerPosition.y - 50}, this->position, 10.f));
  this->projectiles.include(new Projectile(window, {playerPosition.x, playerPosition.y + 50}, this->position, 10.f));
}

void Boss::movimentation(sf::Vector2f playerPosition)
{
  gravity();

  if (playerPosition.x < this->position.x)
  {
    this->speed.x = this->walkSpeed;
    this->position.x -= this->speed.x;
    sprite.setTexture(bossTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, 87, 96));
    sprite.setScale({2.f, 2.f});
  }

  else if (playerPosition.x > this->position.x)
  {
    this->speed.x = this->walkSpeed;
    this->position.x += this->speed.x;
    sprite.setTexture(bossTexture);
    sprite.setTextureRect(sf::IntRect(4, 96, 87, 96));
    sprite.setScale({2.f, 2.f});
  }

  else
  {
  }

  this->rect.setPosition(position);
  this->sprite.setPosition(position);
}

void Boss::update(Entidade::Player::Player1 *p)
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

  /*sf::Time elapsedJump = clockJump.getElapsedTime();
  if (p != NULL)
    if (elapsedJump.asSeconds() >= 3 && (abs(p->getPosition().x - getPosition().x) <= (48 * 2)))
      jumpToAttack(p);*/
}

void Boss::render()
{
  window->draw(healthBar);
  window->draw(sprite);

  projectiles.render();
}

json Boss::getSave()
{
  json j = json::object();

  j["kind"] = BOSS;
  j["positionX"] = position.x;
  j["positionY"] = position.y;
  j["hp"] = this->hp;

  return j;
}

void Boss::jumpToAttack(Entidade::Player::Player1 *p1)
{
  jump();
  if (!onGround)
  {
    // Ja testei na chamada da funcao se o p1 eh diferente de null
    if (getBoundBox().intersects(p1->getBoundBox()))
      p1->setHp(p1->getHp() / 2);
  }
  clock.restart();
}