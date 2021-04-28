// Included to remove \r from players name
#include <algorithm>

#include "characterSelection.h"

using StartScreen::CharacterSelection;

CharacterSelection::CharacterSelection(sf::RenderWindow *window) : isMultiplayer(false),
                                                                   player1Name(""),
                                                                   player2Name(""),
                                                                   contAnimationPlayer1(0),
                                                                   contAnimationPlayer2(0),
                                                                   Menu(window)
{
    if (!player1Image.loadFromFile("src/data/players/Player1Image.png"))
        EXIT_FAILURE;
    if (!player2Image.loadFromFile("src/data/players/player2Image.png"))
        EXIT_FAILURE;
    if (!openMenufont.loadFromFile("src/data/fonts/TurretRoad-Medium.ttf"))
        EXIT_FAILURE;

    menu1.setFont(openMenufont);
    menu1.setCharacterSize(25);
    menu2.setFont(openMenufont);
    menu2.setCharacterSize(25);
    menu3.setFont(openMenufont);
    menu3.setCharacterSize(25);
    menu4.setFont(openMenufont);
    menu4.setCharacterSize(25);

    player1Sprite.setTexture(player1Image);
    player1Sprite.setPosition({550.f, 360.f});
    player2Sprite.setTexture(player2Image);
    player2Sprite.setPosition({815.f, 360.f});
}

CharacterSelection::~CharacterSelection()
{
    window = NULL;
}

int CharacterSelection::Start()
{
    return characterSelection();
}

int CharacterSelection::characterSelection()
{
    int controller = 0;

    menu1.setString("1 Player");
    menu1.setPosition({100.f, 225.f});

    menu2.setString("2 Player");
    menu2.setPosition({100.f, 525.f});

    // Soh arrumando a cor dos menus, se necessario
    updateMenuCollor(0);

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
                        isMultiplayer = false;
                    else if (controller == 1)
                        isMultiplayer = true;
                    return nameCharacterSelection();
                }
            if (controller <= 0)
                controller = 0;
            if (controller >= 1)
                controller = 1;
        }
        player1Animation();
        if (controller)
            player2Animation();
        updateMenuCollor(controller);
        window->draw(menu1);
        window->draw(menu2);
        window->display();
    }
}

// Esse metodo eh interessante, que eh o input dos nomes dos player, nao sei se essa eh a melhor forma de se fazer, mas funciona hahaha
int CharacterSelection::nameCharacterSelection()
{
    int tabPressed = 1;
    int totalChar1 = 0, totalChar2 = 0; // Nao permite extrapolar 14 characteres, essa limitacao estah no if do metodo "player1NameEnter

    player1Name = "";
    player2Name = "";

    menu1.setPosition({340.f, 230.f});
    menu1.setFillColor(sf::Color(sf::Color::White));
    menu1.setCharacterSize(40);
    menu1.setString(player1Name);

    menu2.setPosition({340.f, 270.f});
    menu2.setFillColor(sf::Color(sf::Color::White));
    menu2.setCharacterSize(40);
    menu2.setString(player2Name);

    menu3.setPosition({340.f, 100.f});
    menu3.setFillColor(sf::Color(sf::Color::White));
    menu3.setCharacterSize(30);
    menu3.setString("Type your character name: (Enter to Start)");

    menu4.setPosition({340.f, 50.f});
    menu4.setFillColor(sf::Color(sf::Color::White));
    menu4.setCharacterSize(30);
    menu4.setString("Tab to name other player");

    while (1)
    {
        window->clear();
        sf::Event event;

        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::TextEntered)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
                    tabPressed++;
                if (isMultiplayer)
                {
                    if (tabPressed % 2 == 1)
                        player1NameEnter(totalChar1, event);
                    else
                        player2NameEnter(totalChar2, event);
                    menu2.setString(player2Name);
                }
                else
                    player1NameEnter(totalChar1, event);
                menu1.setString(player1Name);
            }
            // close button clicked
            if (event.type == sf::Event::Closed)
                return EXIT_GAME;

            if (event.type == sf::Event::KeyPressed)
                switch (event.key.code)
                {
                case sf::Keyboard::Return:
                    player1Name.erase(std::remove(player1Name.begin(), player1Name.end(), '\r'), player1Name.end());
                    player2Name.erase(std::remove(player2Name.begin(), player2Name.end(), '\r'), player2Name.end());
                    return PHASE_MANAGER;
                }
            // Soh para nao deixar o valor muito alto, sei lah, vai que ultrapassa o valor maximo do int neh
            if (tabPressed > 1111)
                tabPressed = 0;
        }

        if (isMultiplayer)
        {
            window->draw(menu2);
            window->draw(menu4);
        }
        window->draw(menu1);
        window->draw(menu3);
        window->display();
    }
}

void CharacterSelection::updateMenuCollor(int controller)
{
    if (controller == 0)
    {
        menu1.setFillColor(sf::Color(255, 0, 0, 255));
        menu2.setFillColor(sf::Color(255, 255, 255, 255));
        window->draw(player1Sprite);
    }
    else
    {
        menu1.setFillColor(sf::Color(255, 255, 255, 255));
        menu2.setFillColor(sf::Color(255, 0, 0, 255));
        window->draw(player1Sprite);
        window->draw(player2Sprite);
    }
}

void CharacterSelection::player1Animation()
{
    sf::Time elapsed = clock1.getElapsedTime();
    if (elapsed.asSeconds() >= 0.3)
    {
        contAnimationPlayer1++;
        clock1.restart();
    }
    if (contAnimationPlayer1 > 2)
        contAnimationPlayer1 = 0;
    player1Sprite.setTextureRect(sf::IntRect(47 * contAnimationPlayer1, 48, 47, 48));
}

void CharacterSelection::player2Animation()
{
    sf::Time elapsed = clock2.getElapsedTime();
    if (elapsed.asSeconds() >= 0.3)
    {
        contAnimationPlayer2++;
        clock2.restart();
    }
    if (contAnimationPlayer2 > 2)
        contAnimationPlayer2 = 0;
    player2Sprite.setTextureRect(sf::IntRect(47 * contAnimationPlayer2, 0, 47, 48));
}

void CharacterSelection::player1NameEnter(int &totalChar1, sf::Event &event)
{
    // To not take the tab
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
    {
        // If backspace is pressed, erase the char
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && (totalChar1 > 0))
        {
            player1Name.erase(player1Name.length() - 1);
            totalChar1--;
        }
        else if ((totalChar1 <= 14) && (totalChar1 >= 0)) // Allow any char of the ASCII table
        {
            player1Name += (char)event.text.unicode;
            totalChar1++;
        }
    }
}
void CharacterSelection::player2NameEnter(int &totalChar2, sf::Event &event)
{
    // To not take the tab
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
    {
        // If backspace is pressed, erase the char
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && (totalChar2 > 0))
        {
            player2Name.erase(player2Name.length() - 1);
            totalChar2--;
        }
        else if ((totalChar2 <= 14) && (totalChar2 >= -1)) // Allow any char of the ASCII table
        {
            player2Name += (char)event.text.unicode;
            totalChar2++;
        }
    }
}

void CharacterSelection::setPlayer1Name(const string name1) { player1Name = name1; }
const string CharacterSelection::getPlayer1Name() const { return player1Name; }
void CharacterSelection::setPlayer2Name(const string name2) { player2Name = name2; }
const string CharacterSelection::getPlayer2Name() const { return player2Name; }
void CharacterSelection::setIsMultiplayer(const bool multiplayer) { isMultiplayer = multiplayer; }
const bool CharacterSelection::getIsMultiplayer() const { return isMultiplayer; }