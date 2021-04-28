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

    public:
        RankingScreen(sf::RenderWindow *window = NULL);
        ~RankingScreen();

        int Start() override;
    };
}