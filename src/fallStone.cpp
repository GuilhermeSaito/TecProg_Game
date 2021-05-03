#include "fallStone.h"

using namespace Entidade::Obstacle;

FallStone::FallStone(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage, const int point) : EnemyEntity(window, pos, spee, hP, attackDamage, point)
{
    onGround = false;

    if (!fallStoneTexture.loadFromFile("src/data/obstacles/fallStone.png"))
        EXIT_FAILURE;
    sprite.setTexture(fallStoneTexture);
    sprite.setScale(sf::Vector2f(0.1875, 0.1875));
    sprite.setPosition(pos);

    rect.setPosition(pos);
}
FallStone::~FallStone()
{
    window = NULL;
}

void FallStone::update(Entidade::Player::Player1 *p)
{
    //if (p != NULL)
    //if ((getPosition().x - p->getPosition().x) <= (48 * 4))
    sprite.setPosition(position);

    rect.setPosition(position);
    gravity();
}

void FallStone::render()
{
    window->draw(sprite);
}

json FallStone::getSave()
{
    return NULL;
}

void FallStone::movimentation(sf::Vector2f playerPosition)
{
}
Lists::ProjectilesList *FallStone::getProjectiles()
{
    return NULL;
}