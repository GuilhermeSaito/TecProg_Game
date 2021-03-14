#include "phaseMap3.h"

using namespace PhaseMap;

PhaseMap3::PhaseMap3(std::string path) :
    PhaseMapGeneral(path)
{
    // Transforming the image to 1080 x 720

}
PhaseMap3::~PhaseMap3()
{
}

void PhaseMap3::update(int& controller)
{
    collisionManager.startVerifyCollision();
    if (isPlayerDead())
    {
        controller = PLAYER_DIE;
        return;
    }

    player1->gravity();
    player1->movementation();
    if (player2 != NULL)
    {
        player2->gravity();
        player2->movementation();
    }
    phaseTransition(controller);
}

void PhaseMap3::render(sf::RenderWindow& window, int& controller)
{
    sf::View player1View(sf::Vector2f(player1->getPosition()), sf::Vector2f(1120, 672));
    window.setView(player1View);

    sf::Event event;
    if (window.pollEvent(event))
        switch (event.type)
        {
        case sf::Event::Closed:
            controller = EXIT_GAME;
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        controller = OPTIONS;
        return;
    }

    window.clear();
    renderPhaseBackGround(window);
    player1->draw(window);
    if (player2 != NULL)
        player2->draw(window);
    phaseMapManager.draw(window);
    window.display();
}

void PhaseMap3::renderPhaseBackGround(sf::RenderWindow& window)
{

}