#pragma once

#include "tile.h"
#include <iostream>

namespace PhaseMap
{
    namespace Tiles
    {
        class PhaseMapManager
        {
        private:
            std::vector<std::vector<Tile*>> tileMap;
            int alturaMax;
            int larguraMax;

            std::string path;

        public:
            // Path to the json map phase
            PhaseMapManager(std::string p = "");
            ~PhaseMapManager();

            // false = error
            bool loadMapTileProprieties();
            void draw(sf::RenderWindow& window);

            std::vector<std::vector<Tile*>> getMatrixTile();
            Tile* getTile(int posX, int posY);
            bool isValidTile(int i, int j);

        private:
            void clearMatrix();
        };
    }
}