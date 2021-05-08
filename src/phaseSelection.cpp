#include "phaseSelection.h"
using StartScreen::PhaseSelection;

PhaseSelection::PhaseSelection(sf::RenderWindow *window) : witchPhaseIs(PHASE1),
                                                           Menu(window)
{
    if (!beginnerPhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/beginnerPhaseBackGround.jpeg"))
        EXIT_FAILURE;
    if (!blueOceanPhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/blueOceanPhaseBackGround.png"))
        EXIT_FAILURE;
    if (!cavePhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/cavePhaseBackGround.png"))
        EXIT_FAILURE;
    if (!deathPhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/deathPhaseBackGround.png"))
        EXIT_FAILURE;
    if (!openMenufont.loadFromFile("src/data/fonts/TurretRoad-Medium.ttf"))
        EXIT_FAILURE;

    menu1.setFont(openMenufont);
    menu1.setString("Beginner Phase");
    menu1.setPosition({sf::VideoMode::getDesktopMode().width / 2 - (sf::VideoMode::getDesktopMode().width * (float)0.1), sf::VideoMode::getDesktopMode().height * (float)0.07});
    menu1.setCharacterSize(25);

    menu2.setFont(openMenufont);
    menu2.setString("Blue Ocean Phase");
    menu2.setPosition({sf::VideoMode::getDesktopMode().width / 2 - (sf::VideoMode::getDesktopMode().width * (float)0.1), sf::VideoMode::getDesktopMode().height * (float)0.23});
    menu2.setCharacterSize(25);

    menu3.setFont(openMenufont);
    menu3.setString("Cave Phase");
    menu3.setPosition({sf::VideoMode::getDesktopMode().width / 2 - (sf::VideoMode::getDesktopMode().width * (float)0.1), sf::VideoMode::getDesktopMode().height * (float)0.41});
    menu3.setCharacterSize(25);

    menu4.setFont(openMenufont);
    menu4.setString("Death Phase");
    menu4.setPosition({sf::VideoMode::getDesktopMode().width / 2 - (sf::VideoMode::getDesktopMode().width * (float)0.1), sf::VideoMode::getDesktopMode().height * (float)0.61});
    menu4.setCharacterSize(25);

    menu5.setFont(openMenufont);
    menu5.setString("Threaded Level");
    menu5.setPosition({sf::VideoMode::getDesktopMode().width / 2 - (sf::VideoMode::getDesktopMode().width * (float)0.1), sf::VideoMode::getDesktopMode().height * (float)0.79});
    menu5.setCharacterSize(25);

    beginnerPhaseSprite.setTexture(beginnerPhaseBackGround);
    // Width 550, Height 690
    beginnerPhaseSprite.setScale(sf::Vector2f(0.2865, 0.66));
    beginnerPhaseSprite.setPosition({sf::VideoMode::getDesktopMode().width / 2 + (sf::VideoMode::getDesktopMode().width * (float)0.07), 15.f});
    blueOceanPhaseSprite.setTexture(blueOceanPhaseBackGround);
    blueOceanPhaseSprite.setScale(sf::Vector2f(0.1571, 0.3504));
    blueOceanPhaseSprite.setPosition({sf::VideoMode::getDesktopMode().width / 2 + (sf::VideoMode::getDesktopMode().width * (float)0.07), 20.f});
    cavePhaseSprite.setTexture(cavePhaseBackGround);
    cavePhaseSprite.setScale(sf::Vector2f(0.1572, 0.3504));
    cavePhaseSprite.setPosition({sf::VideoMode::getDesktopMode().width / 2 + (sf::VideoMode::getDesktopMode().width * (float)0.07), 20.f});
    deathPhaseSprite.setTexture(deathPhaseBackGround);
    deathPhaseSprite.setScale(sf::Vector2f(0.4297, 0.9584));
    deathPhaseSprite.setPosition({sf::VideoMode::getDesktopMode().width / 2 + (sf::VideoMode::getDesktopMode().width * (float)0.07), 20.f});
}
PhaseSelection::~PhaseSelection()
{
    window = NULL;
}

const int PhaseSelection::Start()
{
    return phaseSelection();
}

int PhaseSelection::phaseSelection()
{
    int controller = 0;

    while (1)
    {
        window->clear();
        sf::Event event;
        if (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                return EXIT_GAME;
            if (event.type == sf::Event::KeyPressed)
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    controller--;
                    break;
                case sf::Keyboard::Down:
                    controller++;
                    break;

                case sf::Keyboard::Return:
                    if (controller == 0)
                        witchPhaseIs = PHASE1;
                    else if (controller == 1)
                        witchPhaseIs = PHASE2;
                    else if (controller == 2)
                        witchPhaseIs = PHASE3;
                    else if (controller == 3)
                        witchPhaseIs = PHASE4;
                    else
                        witchPhaseIs = EXTRALEVEL;
                    return CHARACTER_SELECTION;
                }
            if (controller <= 0)
                controller = 5;
            if (controller >= 5)
                controller = 0;
        }
        updateMenuCollor(controller);
        window->draw(menu1);
        window->draw(menu2);
        window->draw(menu3);
        window->draw(menu4);
        window->draw(menu5);
        window->display();
    }
}

void PhaseSelection::updateMenuCollor(int controller)
{
    if (controller == 0)
    {
        menu1.setFillColor(sf::Color(255, 0, 0, 255));
        menu2.setFillColor(sf::Color(255, 255, 255, 255));
        menu3.setFillColor(sf::Color(255, 255, 255, 255));
        menu4.setFillColor(sf::Color(255, 255, 255, 255));
        menu5.setFillColor(sf::Color(255, 255, 255, 255));
        window->draw(beginnerPhaseSprite);
    }
    else if (controller == 1)
    {
        menu1.setFillColor(sf::Color(255, 255, 255, 255));
        menu2.setFillColor(sf::Color(255, 0, 0, 255));
        menu3.setFillColor(sf::Color(255, 255, 255, 255));
        menu4.setFillColor(sf::Color(255, 255, 255, 255));
        menu5.setFillColor(sf::Color(255, 255, 255, 255));
        window->draw(blueOceanPhaseSprite);
    }
    else if (controller == 2)
    {
        menu1.setFillColor(sf::Color(255, 255, 255, 255));
        menu2.setFillColor(sf::Color(255, 255, 255, 255));
        menu3.setFillColor(sf::Color(255, 0, 0, 255));
        menu4.setFillColor(sf::Color(255, 255, 255, 255));
        menu5.setFillColor(sf::Color(255, 255, 255, 255));
        window->draw(cavePhaseSprite);
    }
    else if (controller == 3)
    {
        menu1.setFillColor(sf::Color(255, 255, 255, 255));
        menu2.setFillColor(sf::Color(255, 255, 255, 255));
        menu3.setFillColor(sf::Color(255, 255, 255, 255));
        menu4.setFillColor(sf::Color(255, 0, 0, 255));
        menu5.setFillColor(sf::Color(255, 255, 255, 255));
        window->draw(deathPhaseSprite);
    }
    else
    {
        menu1.setFillColor(sf::Color(255, 255, 255, 255));
        menu2.setFillColor(sf::Color(255, 255, 255, 255));
        menu3.setFillColor(sf::Color(255, 255, 255, 255));
        menu4.setFillColor(sf::Color(255, 255, 255, 255));
        menu5.setFillColor(sf::Color(255, 0, 0, 255));
        window->draw(deathPhaseSprite);
    }
}

void PhaseSelection::setWitchPhaseIs(const int phaseIs) { witchPhaseIs = phaseIs; }
const int PhaseSelection::getWitchPhaseIs() const { return witchPhaseIs; }