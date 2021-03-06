#include "spikeTrap.h"

using namespace Entidade::Obstacle;

SpikeTrap::SpikeTrap(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage, const int point) : EnemyEntity(window, pos, spee, hP, attackDamage, point)
{
    if (!spikeTrapTexture.loadFromFile("src/data/obstacles/spikeTrap.png"))
        EXIT_FAILURE;
    sprite.setTexture(spikeTrapTexture);
    sprite.setScale(sf::Vector2f(0.12972973, 0.12972973));
    sprite.setPosition(pos);

    rect.setPosition(pos);
}
SpikeTrap::~SpikeTrap()
{
    window = NULL;
}

void SpikeTrap::update(Entidade::Player::Player1 *p)
{
    if (!onGround)
        gravity();
}

void SpikeTrap::render()
{
    window->draw(sprite);
}

json SpikeTrap::getSave()
{
    return NULL;
}

void SpikeTrap::movimentation(sf::Vector2f playerPosition)
{
}
Lists::ProjectilesList *SpikeTrap::getProjectiles()
{
    return NULL;
}