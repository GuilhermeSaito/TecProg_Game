#include "boss.h"
#include "thread.h"
#include "player1.h"

#pragma once

namespace Tred
{
    class ThreadedBoss : public Tred::Thread, public Entidade::Enemy::Boss
    {
    private:
        bool continuing;
        bool paused;

        Entidade::Player::Player1 *player1;

        void run() override;

    public:
        ThreadedBoss(sf::RenderWindow *window = NULL, sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0, const int point = 0);
        ~ThreadedBoss();

        void setPlayer1(Entidade::Player::Player1 *p1);
    };
}