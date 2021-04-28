#pragma once

#include "tileManager.h"

namespace PhaseMap
{
    namespace Tiles
    {
        class Tile
        {
        private:
            int numProprietieTile;

            sf::RectangleShape rectTile;
            sf::Sprite tileSprite;
            sf::Vector2f spaceOcuped;

            sf::RenderWindow *window;

        public:
            Tile(sf::RenderWindow *window = NULL, int numTile = 0, sf::Vector2f spaceOcup = {0, 0});
            ~Tile();

            void draw();

            sf::FloatRect getBoundBox();

            sf::Vector2f getPosition();

            int getNumTile();
        };
    }
}