#include "tileManager.h"

using namespace PhaseMap::Tiles;

TileManager::TileManager()
{
}

TileManager::~TileManager()
{
}


sf::Texture* TileManager::getTileTexture(int tileType, sf::RectangleShape& rect, sf::Vector2f& spaceOcuped)
{
    switch (tileType)
    {
    case BrickFloor:
        rect.setSize(sf::Vector2f(48, 48));
        rect.setPosition(sf::Vector2f(spaceOcuped));
        return Data::getInstance()->getBrickFloor();
        break;
    case IceFloor:
        rect.setSize(sf::Vector2f(48, 48));
        rect.setPosition(sf::Vector2f(spaceOcuped));
        return Data::getInstance()->getIceFloor();
        break;
    case IceFloor2:
        rect.setSize(sf::Vector2f(48, 48));
        rect.setPosition(sf::Vector2f(spaceOcuped));
        return Data::getInstance()->getIceFloor2();
        break;
    case PurpleFloor:
        rect.setSize(sf::Vector2f(48, 48));
        rect.setPosition(sf::Vector2f(spaceOcuped));
        return Data::getInstance()->getPurpleFloor();
        break;

    default:
        return Data::getInstance()->getNotImplementedYet();
        break;
    }
}