#include "flyingEnemy.h"
//here are the defined numbers for the wave function that will be used in movimentation
#define AMPLITUDE 40.0
#define ANGULARSPEED 2.0

using namespace Entidade::Enemy;

FlyingEnemy::FlyingEnemy(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage, const int point) : ShooterEntity(window, pos, spee, hP, attackDamage, point),
                                                                                                                                         originalYposition(pos.y)
{
  if (!flyingEnemyTexture.loadFromFile("src/data/enemy/reaperFlyTexture.png"))
    EXIT_FAILURE;

  this->hasProjectiles = true;
  this->walkSpeed = spee.x;

  rect.setSize(sf::Vector2f(38.f, 42.f));
  rect.setPosition(pos);

  sprite.setTexture(flyingEnemyTexture);
  sprite.setTextureRect(sf::IntRect(2, 2, 38, 42));
  sprite.setScale({2.f, 2.f});
  sprite.setPosition(rect.getPosition());

  healthBar.setFillColor(sf::Color::Red);
  healthBar.setPosition(sf::Vector2f(position.x - 10, position.y - 25));
}
FlyingEnemy::~FlyingEnemy()
{
  window = NULL;
  this->projectiles.setNull();
}

void FlyingEnemy::shootProjectile(sf::Vector2f playerPosition)
{
  if (!this->projectiles.isEmpty())
    this->projectiles.setNull();

  this->projectiles.include(new Projectile(window, {this->position.x, this->position.y + 50}, this->position, 10.f));
  this->projectiles.include(new Projectile(window, {this->position.x - 50, this->position.y + 50}, this->position, 10.f));
  this->projectiles.include(new Projectile(window, {this->position.x + 50, this->position.y + 50}, this->position, 10.f));
}

void FlyingEnemy::movimentation(sf::Vector2f playerPosition)
{

  if (playerPosition.x < this->position.x)
  {
    this->speed.x = this->walkSpeed;
    this->position.x -= this->speed.x;
    sprite.setTexture(flyingEnemyTexture);
    sprite.setScale({2.f, 2.f});
    sprite.setTextureRect(sf::IntRect(2, 2, 38, 42));
  }

  else if (playerPosition.x > this->position.x)
  {
    this->speed.x = this->walkSpeed;
    this->position.x += this->speed.x;
    sprite.setTexture(flyingEnemyTexture);
    sprite.setScale({-2.f, 2.f});
  }

  this->elapsed = this->clock.getElapsedTime();
  //the wave equasion is being applied here
  this->position.y = this->originalYposition + (AMPLITUDE * cos(ANGULARSPEED * (elapsed.asSeconds())));

  this->rect.setPosition(position);
  this->sprite.setPosition(position);
}

void FlyingEnemy::update(Entidade::Player::Player1 *p)
{
  healthBar.setSize(sf::Vector2f(hp, 5.f));
  healthBar.setPosition(sprite.getPosition().x - 10, sprite.getPosition().y - 20);
  movimentation(p->getPosition());

  this->elapsed = this->clock.getElapsedTime();
  if (this->elapsed.asSeconds() >= 4.0)
  {
    shootProjectile(p->getPosition());
    clock.restart();
  }

  if (!this->projectiles.isEmpty())
    projectiles.update(p);
}

void FlyingEnemy::render()
{
  window->draw(healthBar);
  window->draw(sprite);

  projectiles.render();
}

json FlyingEnemy::getSave()
{
  json j = json::object();

  j["kind"] = FLYING_ENEMY;
  j["positionX"] = this->position.x;
  j["positionY"] = this->position.y;
  j["hp"] = this->hp;

  return j;
}