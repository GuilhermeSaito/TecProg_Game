#include "zombie.h"

using namespace Entidade::Enemy;

Zombie::Zombie(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage, const int point, const int rQt) : EnemyEntity(window, pos, spee, hP, attackDamage, point),
                                                                                                                                              initialHp(hP),
                                                                                                                                              resurrectionQuantity(rQt)
{
  if (!zombieTexture.loadFromFile("src/data/enemy/zombieTexture.png"))
    EXIT_FAILURE;

  this->hasProjectiles = false;
  this->walkSpeed = spee.x;

  rect.setSize(sf::Vector2f(32.f, 47.f));
  rect.setPosition(pos);

  sprite.setTexture(zombieTexture);
  sprite.setTextureRect(sf::IntRect(0, 0, 32, 47));
  sprite.setPosition(rect.getPosition());

  healthBar.setFillColor(sf::Color::Red);
  // Apagar esse setPosition do healthBar, pois ele vai ficar atualizando quando o inimigo se mover
  healthBar.setPosition(sf::Vector2f(position.x - 10, position.y - 25));
}
Zombie::~Zombie()
{
  window = NULL;
}

void Zombie::movimentation(sf::Vector2f playerPosition)
{
  gravity();

  if (playerPosition.x <= this->position.x)
  {
    this->speed.x = this->walkSpeed;
    this->position.x -= this->speed.x;
    sprite.setTexture(zombieTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 47));
  }

  else if (playerPosition.x > this->position.x)
  {
    this->speed.x = this->walkSpeed;
    this->position.x += this->speed.x;
    sprite.setTexture(zombieTexture);
    sprite.setTextureRect(sf::IntRect(2, 50, 32, 47));
  }

  this->rect.setPosition(position);
  this->sprite.setPosition(position);
}

void Zombie::update(Entidade::Player::Player1 *p)
{
  if (getHp() <= 0)
  {
    if (resurrectionQuantity > 0)
    {
      resurrectionQuantity--;
      setHp(initialHp);
    }
  }

  healthBar.setSize(sf::Vector2f(hp, 5.f));
  healthBar.setPosition(sprite.getPosition().x - 10, sprite.getPosition().y - 20);
  movimentation(p->getPosition());
}

void Zombie::render()
{
  window->draw(healthBar);
  window->draw(sprite);
}

Lists::ProjectilesList *Zombie::getProjectiles()
{
  return NULL;
}

// guarda as informações do zumbi dentro de um objeto json
json Zombie::getSave()
{
  json j = json::object();

  j["kind"] = ZOMBIE;
  j["positionX"] = this->position.x;
  j["positionY"] = this->position.y;
  j["hp"] = this->hp;

  return j;
}