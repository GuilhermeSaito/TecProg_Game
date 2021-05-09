#include "threadedBoss.h"

using namespace Tred;

ThreadedBoss::ThreadedBoss(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage, const int point) : continuing(true),
                                                                                                                                           paused(false),
                                                                                                                                           Boss(window, pos, spee, hP, attackDamage, point),
                                                                                                                                           player1(NULL)
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
ThreadedBoss::~ThreadedBoss()
{
    player1 = NULL;
}

void ThreadedBoss::run()
{
    if (player1 != NULL)
        update(player1);
    render();
}

void ThreadedBoss::setPlayer1(Entidade::Player::Player1 *p1) { player1 = p1; }