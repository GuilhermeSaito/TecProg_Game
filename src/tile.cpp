#include "tile.h"

using namespace PhaseMap::Tiles;


Tile::Tile(int numTle, sf::Vector2f spaceOcup) :
    numProprietieTile{ numTle },
    spaceOcuped{ spaceOcup }
{
    if (numTle != 0)
    {
        tileSprite.setTexture(*(tileManager.getTileTexture(numTle, rectTile, spaceOcup)));
        tileSprite.setPosition(rectTile.getPosition());
    }
}

Tile::~Tile()
{
}

void Tile::draw(sf::RenderWindow& window)
{
    if (numProprietieTile != 0)
        window.draw(tileSprite);
}

sf::FloatRect Tile::getBoundBox()
{
    return sf::FloatRect(spaceOcuped.x, spaceOcuped.y, rectTile.getSize().x, rectTile.getSize().y);
}

sf::Vector2f Tile::getPosition()
{
    return spaceOcuped;
}

int Tile::getNumTile()
{
    return numProprietieTile;
}