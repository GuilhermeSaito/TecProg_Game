#pragma once

#include "menu.h"

namespace Screen
{
    class PlayerDieScreen : public Menu
    {
    private:
        sf::Texture playerDieTexture;

        sf::Music music;

    public:
        PlayerDieScreen(sf::RenderWindow *window = NULL);
        ~PlayerDieScreen();

        const int Start() override;
    };
}