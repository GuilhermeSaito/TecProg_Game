#pragma once

#include "data.h"

namespace PhaseMap
{
	namespace Tiles
	{
		class TileManager
		{
		private:
			enum TileType
			{
				BrickFloor = 1,
				IceFloor = 2,
				IceFloor2 = 3,
				PurpleFloor = 4,
				Spike = 5
			};

		public:
			TileManager();
			~TileManager();

			sf::Texture* getTileTexture(int tileType, sf::RectangleShape& rect, sf::Vector2f& spaceOcuped);
		};
	}
}
