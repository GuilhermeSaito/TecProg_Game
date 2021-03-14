#pragma once

#include "tileManager.h"

namespace PhaseMap
{
	namespace Tiles
	{
		class Tile
		{
        private:
            TileManager tileManager;

            int numProprietieTile;

            sf::RectangleShape rectTile;
            sf::Sprite tileSprite;
            sf::Vector2f spaceOcuped;

        public:
            Tile(int numTile = 0, sf::Vector2f spaceOcup = { 0, 0 });
            ~Tile();

            void draw(sf::RenderWindow& window);

            sf::FloatRect getBoundBox();

            sf::Vector2f getPosition();

            int getNumTile();
        };
	}
}