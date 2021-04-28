#pragma once

#include "menu.h"
#include "save.h"
#include "data.h"

class RankingScreen : public Menu
{
private:
    SaveGame::Save save;

public:
    RankingScreen(sf::RenderWindow *window = NULL);
    ~RankingScreen();

    int Start() override;
};