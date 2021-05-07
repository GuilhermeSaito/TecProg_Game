#include "threadedBoss.h"

namespace Thread
{
    ThreadedBoss::ThreadedBoss(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage, const int point, Entidade::Player::Player1* p): 
                                                                                                                                                                        continuing(true), 
                                                                                                                                                                        paused(false)                                                                                                                                                                   
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
    }

    void ThreadedBoss::movimentation(sf::Vector2f playerPosition)
    {
    if (!onGround)
        gravity();

    if (playerPosition.x < this->position.x)
    {
        this->speed.x = this->walkSpeed;
        this->position.x -= this->speed.x;
        sprite.setTexture(bossTexture);
        sprite.setTextureRect(sf::IntRect(0, 0, 87, 96));
        sprite.setScale({2.f, 2.f});
    }

    else if (playerPosition.x > this->position.x)
    {
        this->speed.x = this->walkSpeed;
        this->position.x += this->speed.x;
        sprite.setTexture(bossTexture);
        sprite.setTextureRect(sf::IntRect(4, 96, 87, 96));
        sprite.setScale({2.f, 2.f});
    }

    else
    {
    }

    this->rect.setPosition(position);
    this->sprite.setPosition(position);
    }

    //a função faz a atualização do boss
    void ThreadedBoss::update()
    {
        healthBar.setSize(sf::Vector2f(hp, 5.f));
        healthBar.setPosition(sprite.getPosition().x - 10, sprite.getPosition().y - 20);
        movimentation({400.f, 400.f});

        /*sf::Time elapsedJump = clockJump.getElapsedTime();
        if (p != NULL)
            if (elapsedJump.asSeconds() >= 3 && (abs(p->getPosition().x - getPosition().x) <= (48 * 2)))
            jumpToAttack(p);*/
    }

    void ThreadedBoss::render()
    {
        if (window != NULL)
        {
            window->draw(healthBar);
            window->draw(sprite);
        }
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
                update();
                //render();

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