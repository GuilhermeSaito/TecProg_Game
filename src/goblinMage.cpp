#include "goblinMage.h"

using namespace Entidade::Enemy;

GoblinMage::GoblinMage(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage, const int point) : ShooterEntity(window, pos, spee, hP, attackDamage, point)
{
  if (!goblinMageTexture.loadFromFile("src/data/enemy/goblinMageTexture.png"))
    EXIT_FAILURE;

  this->hasProjectiles = true;
  this->walkSpeed = spee.x;

  rect.setSize(sf::Vector2f(33.f, 45.f));
  rect.setPosition(pos);

  sprite.setTexture(goblinMageTexture);
  sprite.setTextureRect(sf::IntRect(0, 0, 33, 45));
  sprite.setPosition(rect.getPosition());

  healthBar.setFillColor(sf::Color::Red);
  // Apagar esse setPosition do healthBar, pois ele vai ficar atualizando quando o inimigo se mover
  healthBar.setPosition(sf::Vector2f(position.x - 10, position.y - 25));
}
GoblinMage::~GoblinMage()
{
  window = NULL;
  this->projectiles.setNull();
}

void GoblinMage::shootProjectile(sf::Vector2f playerPosition)
{
  if (this->projectiles.getQuantity() > 3)
  {
    this->projectiles.kill(projectiles.getFirst());
    this->projectiles.setQuantity(this->projectiles.getQuantity() - 1);
  }

  this->projectiles.include(new Projectile(window, playerPosition, this->position, 10.f));
}

void GoblinMage::movimentation(sf::Vector2f playerPosition)
{
  gravity();

  if (playerPosition.x <= this->position.x)
  {
    this->speed.x = this->walkSpeed;
    this->position.x -= this->speed.x;
    sprite.setTexture(goblinMageTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 47));
  }

  else if (playerPosition.x > this->position.x)
  {
    this->speed.x = this->walkSpeed;
    this->position.x += this->speed.x;
    sprite.setTexture(goblinMageTexture);
    sprite.setTextureRect(sf::IntRect(2, 49, 32, 47));
  }

  else
  {
  }

  this->rect.setPosition(position);
  this->sprite.setPosition(position);
}

void GoblinMage::update(Entidade::Player::Player1 *p)
{
  healthBar.setSize(sf::Vector2f(hp, 5.f));
  healthBar.setPosition(sprite.getPosition().x - 10, sprite.getPosition().y - 20);
  movimentation(p->getPosition());

  this->elapsed = this->clock.getElapsedTime();
  if (this->elapsed.asSeconds() >= 3.0)
  {
    shootProjectile(p->getPosition());
    clock.restart();
  }

  if (!this->projectiles.isEmpty())
    projectiles.update(p);
}

void GoblinMage::render()
{
  window->draw(healthBar);
  window->draw(sprite);

  this->projectiles.render();
}

json GoblinMage::getSave()
{
  json j = json::object();

  j["kind"] = GOBLIN_MAGE;
  j["positionX"] = this->position.x;
  j["positionY"] = this->position.y;
  j["hp"] = this->hp;

  return j;
}
