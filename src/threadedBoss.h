#include "boss.h"
#include "thread.h"
#include <chrono>

#pragma once

namespace Thread
{
    class ThreadedBoss: public Thread::Thread , public Entidade::Enemy::Boss
    {
    private:
        bool continuing;
        bool paused;

        void run() override;

        Entidade::Player::Player1* player1;

    public:
        ThreadedBoss(sf::RenderWindow *window = NULL, sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0, const int point = 0, Entidade::Player::Player1* p = NULL);
        ~ThreadedBoss();

        void stopUpdating();
        void setPaused(bool p);
    };
}