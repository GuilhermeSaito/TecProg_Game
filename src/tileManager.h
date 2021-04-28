#pragma once

#include <SFML/Graphics.hpp>

// Vou fazer essa classe como Singleton, porque como estah, cada tile teria 1 tileManager.
// Ou seja, cada tile tem todos esses carregados, ai em vez de fazer isso, vou fazer cada tile acessar 1 tileManager
namespace PhaseMap
{
	namespace Tiles
	{
		class TileManager
		{
		private:
			TileManager();
			static TileManager *instance;

			enum TileType
			{
				BrickFloor = 1,
				IceFloor = 2,
				IceFloor2 = 3,
				PurpleFloor = 4,
				Spike = 5
			};

			sf::Texture brickFloor;
			sf::Texture iceFloor;
			sf::Texture iceFloor2;
			sf::Texture purpleFloor;

		public:
			~TileManager();
			static TileManager *getInstance();

			sf::Texture *getTileTexture(int tileType, sf::RectangleShape &rect, sf::Vector2f &spaceOcuped);
		};
	}
}
