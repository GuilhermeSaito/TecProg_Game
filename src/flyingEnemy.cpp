#include "flyingEnemy.h"
//here are the defined numbers for the wave function that will be used in movimentation
#define AMPLITUDE 40.0
#define ANGULARSPEED 2.0

using namespace Entidade::Enemy;

FlyingEnemy::FlyingEnemy(sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage) :
	  EnemyEntity(pos, spee, hP, attackDamage),
    projectiles(),
    clock(),
    originalYposition(pos.y)
{
    this->walkSpeed = spee.x;

    rect.setSize(sf::Vector2f(38.f, 42.f));
    rect.setPosition(pos);

    sprite.setTexture(*(Data::getInstance()->getFlyingEnemyTexture()));
    sprite.setTextureRect(sf::IntRect(2, 2, 38, 42));
    sprite.setScale({2.f, 2.f});
    sprite.setPosition(rect.getPosition());

    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition(sf::Vector2f(position.x - 10, position.y - 25));
}
FlyingEnemy::~FlyingEnemy()
{
    this->projectiles.setNull();
}

ListElement<Projectile>* FlyingEnemy::getProjectiles()
{
  return &this->projectiles;
}

void FlyingEnemy::shootProjectile()
{ 
    if (!this->projectiles.isEmpty())
        this->projectiles.setNull();

    this->projectiles.include(new Projectile({this->position.x, this->position.y+50}, this->position, 10.f));
    this->projectiles.include(new Projectile({this->position.x-50, this->position.y+50}, this->position, 10.f));
    this->projectiles.include(new Projectile({this->position.x+50, this->position.y+50}, this->position, 10.f));
}

void FlyingEnemy::movimentation(sf::Vector2f playerPosition)
{

    if (playerPosition.x < this->position.x)
    {
        this->speed.x = this->walkSpeed;
        this->position.x -= this->speed.x;
        sprite.setTexture(*(Data::getInstance()->getFlyingEnemyTexture()));
        sprite.setScale({2.f, 2.f});
        sprite.setTextureRect(sf::IntRect(2, 2, 38, 42));
    }

    else if (playerPosition.x > this->position.x)
    {
        this->speed.x = this->walkSpeed;
        this->position.x +=this->speed.x;
        sprite.setTexture(*(Data::getInstance()->getFlyingEnemyTexture()));
        sprite.setScale({-2.f, 2.f});
    }

    this->elapsed = this->clock.getElapsedTime();
    //the wave equasion is being applied here
    this->position.y = this->originalYposition + (AMPLITUDE*cos(ANGULARSPEED*(elapsed.asSeconds())));

    this->rect.setPosition(position);
    this->sprite.setPosition(position);
}

void FlyingEnemy::update(Entidade::Player::Player1* p)
{
  healthBar.setSize(sf::Vector2f(hp, 5.f));
  healthBar.setPosition(sprite.getPosition().x - 10, sprite.getPosition().y - 20);
  movimentation(p->getPosition());

  this->elapsed = this->clock.getElapsedTime();
  if (this->elapsed.asSeconds() >= 4.0)
  {
    shootProjectile();
    clock.restart();
  }

  if (!this->projectiles.isEmpty())
    projectiles.update(p);
}

void FlyingEnemy::render(sf::RenderWindow& window)
{
	window.draw(healthBar);
	window.draw(sprite);

  projectiles.render(window);
}

json FlyingEnemy::getSave()
{
  json j = json::object();

  j["flyingEnemy"]["positionX"] = position.x;
  j["flyingEnemy"]["positionY"] = position.y;

  return j;
}