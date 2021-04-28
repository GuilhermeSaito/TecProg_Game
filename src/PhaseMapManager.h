#pragma once

#include "tile.h"
#include "menu.h"
#include <iostream>

namespace PhaseMap
{
    namespace Tiles
    {
        class PhaseMapManager : public Menu
        {
        private:
            std::vector<std::vector<Tile *>> tileMap;
            int alturaMax;
            int larguraMax;

            std::string path;

        public:
            // Path to the json map phase
            PhaseMapManager(sf::RenderWindow *window = NULL, std::string p = "");
            ~PhaseMapManager();

            // false = error
            bool loadMapTileProprieties();
            void draw();

            std::vector<std::vector<Tile *>> getMatrixTile();
            Tile *getTile(int posX, int posY);
            bool isValidTile(int i, int j);

        private:
            void clearMatrix();

            int Start() override { return 1; }
        };
    }
}