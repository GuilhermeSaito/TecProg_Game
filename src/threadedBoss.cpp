#include "threadedBoss.h"

namespace Thread
{
    ThreadedBoss::ThreadedBoss(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage, const int point, Entidade::Player::Player1* p): 
                                                                                                                                                                        continuing(true), 
                                                                                                                                                                        paused(false), 
                                                                                                                                                                        player1(p)
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
        this->continuing = true;

        while(this->continuing)
        {
            if (!paused)
            {
                lock();
                //player feito como singleton class principalmente pela classe thread
                update(player1);

                //espera de 2 segundos para a mudança do mutex
                std::chrono::duration<double> wait = std::chrono::milliseconds(2000);
                auto waiting_basis = std::chrono::steady_clock::now();

                while (wait > std::chrono::milliseconds(0))
                {
                    if (!paused && continuing)
                        wait -= std::chrono::steady_clock::now() - waiting_basis;

                    waiting_basis = std::chrono::steady_clock::now();
                    yield();
                }
                unlock();

                wait = std::chrono::milliseconds(200);
                waiting_basis = std::chrono::steady_clock::now();

                while (wait > std::chrono::milliseconds(0))
                {
                    if (!paused && continuing)
                        wait -= std::chrono::steady_clock::now() - waiting_basis;

                    waiting_basis = std::chrono::steady_clock::now();
                    yield();
                }
            }
            //apenas para não ficar chamando a biblioteca chrono enquanto está pausado
            else
            {
                yield();
            }
        }
    }
    void ThreadedBoss::stopUpdating()
    {
        this->continuing = false;
    }
    void ThreadedBoss::setPaused(bool p)
    {
        this->paused = p;
    }
}