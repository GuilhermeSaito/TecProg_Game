#include "tile.h"

using namespace PhaseMap::Tiles;

Tile::Tile(sf::RenderWindow *window, int numTle, sf::Vector2f spaceOcup) : numProprietieTile{numTle},
                                                                           spaceOcuped{spaceOcup}
{
    if (numTle != 0)
    {
        tileSprite.setTexture(*(TileManager::getInstance()->getTileTexture(numTle, rectTile, spaceOcup)));
        tileSprite.setPosition(rectTile.getPosition());
    }
    this->window = window;
}

Tile::~Tile()
{
    window = NULL;
}

void Tile::draw()
{
    if (numProprietieTile != 0)
        window->draw(tileSprite);
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