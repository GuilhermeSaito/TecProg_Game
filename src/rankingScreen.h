#pragma once

#include "menu.h"
#include "save.h"

namespace Screen
{
    class RankingScreen : public Menu
    {
    private:
        SaveGame::Save save;
        sf::Texture rankingScreenTexture;
        sf::Font openMenufont;

        sf::Music music;

    public:
        RankingScreen(sf::RenderWindow *window = NULL);
        ~RankingScreen();

        const int Start() override;
    };
}