#pragma once

#include "menu.h"

namespace Screen
{
    class PlayerDieScreen : public Menu
    {
    private:
        sf::Texture playerDieTexture;

    public:
        PlayerDieScreen(sf::RenderWindow *window = NULL);
        ~PlayerDieScreen();

        int Start() override;
    };
}