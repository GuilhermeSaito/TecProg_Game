#include "rankingScreen.h"

using namespace Screen;

RankingScreen::RankingScreen(sf::RenderWindow *window) : Menu(window)
{
    if (!rankingScreenTexture.loadFromFile("src/data/gameClear/gameClear.jpeg"))
        EXIT_FAILURE;
    if (!openMenufont.loadFromFile("src/data/fonts/TurretRoad-Medium.ttf"))
        EXIT_FAILURE;
}

RankingScreen::~RankingScreen()
{
    window = NULL;
}

int RankingScreen::Start()
{
    std::vector<std::vector<sf::Text *>> namesScoreDisplay;
    std::string temp;
    int cont = 1;

    json j = save.rankingRecover();
    for (auto &i : j["ranking"])
    {
        if (cont >= 5)
            break;

        std::vector<sf::Text *> l;

        sf::Text *player1Name = new sf::Text;
        player1Name->setFont(openMenufont);
        player1Name->setCharacterSize(22);
        player1Name->setFillColor(sf::Color::White);
        temp = i["state"]["player1Name"];
        player1Name->setString("Player1 Name:  " + temp);
        player1Name->setPosition({300.f, 130.f + (20 * cont)});
        l.push_back(player1Name);
        if (i["state"]["multiplayer"])
        {

            sf::Text *player2Name = new sf::Text;
            player2Name->setFont(openMenufont);
            player2Name->setCharacterSize(22);
            player2Name->setFillColor(sf::Color::White);
            temp = i["state"]["player2Name"];
            player2Name->setString("Player2 Name:  " + temp);
            player2Name->setPosition({500.f, 130.f + (20 * cont)});
            l.push_back(player2Name);
        }
        sf::Text *score = new sf::Text;
        score->setFont(openMenufont);
        score->setCharacterSize(22);
        score->setFillColor(sf::Color::White);
        temp = std::to_string(i["state"]["score"].get<int>());
        score->setString("Score:  " + temp);
        score->setPosition({700.f, 130.f + (20 * cont)});
        l.push_back(score);

        namesScoreDisplay.push_back(l);

        cont++;
    }

    sf::Sprite sprite;
    sprite.setTexture(rankingScreenTexture);
    sprite.setScale(sf::Vector2f(1.7, 1.5));
    sprite.setPosition({-80, 0});

    window->clear();
    window->draw(sprite);
    for (std::vector<sf::Text *> i : namesScoreDisplay)
        for (auto *j : i)
            window->draw(*j);
    window->display();

    while (1)
    {
        sf::Event evet;
        if (window->pollEvent(evet))
            switch (evet.type)
            {
            case sf::Event::MouseButtonPressed:
                for (std::vector<sf::Text *> i : namesScoreDisplay)
                    for (auto *j : i)
                        delete j;
                namesScoreDisplay.clear();
                return OPEN_MENU;
            case sf::Event::Closed:
                for (std::vector<sf::Text *> i : namesScoreDisplay)
                    for (auto *j : i)
                        delete j;
                namesScoreDisplay.clear();
                return EXIT_GAME;
            }
    }
}