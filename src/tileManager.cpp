#include "tileManager.h"

using namespace PhaseMap::Tiles;

TileManager *TileManager::instance = NULL;

TileManager::TileManager()
{
    if (!brickFloor.loadFromFile("src/data/phaseMap/tilesUsed/BrickFloor.jpg"))
        EXIT_FAILURE;
    if (!iceFloor.loadFromFile("src/data/phaseMap/tilesUsed/iceFloor1.jpg"))
        EXIT_FAILURE;
    if (!iceFloor2.loadFromFile("src/data/phaseMap/tilesUsed/iceFloor2.jpg"))
        EXIT_FAILURE;
    if (!purpleFloor.loadFromFile("src/data/phaseMap/tilesUsed/purpleFloor.jpg"))
        EXIT_FAILURE;
}

TileManager::~TileManager()
{
    instance = NULL;
}

TileManager *TileManager::getInstance()
{
    if (instance == NULL)
        instance = new TileManager();
    return instance;
}

sf::Texture *TileManager::getTileTexture(int tileType, sf::RectangleShape &rect, sf::Vector2f &spaceOcuped)
{
    switch (tileType)
    {
    case BrickFloor:
        rect.setSize(sf::Vector2f(48, 48));
        rect.setPosition(sf::Vector2f(spaceOcuped));
        return &brickFloor;
    case IceFloor:
        rect.setSize(sf::Vector2f(48, 48));
        rect.setPosition(sf::Vector2f(spaceOcuped));
        return &iceFloor;
    case IceFloor2:
        rect.setSize(sf::Vector2f(48, 48));
        rect.setPosition(sf::Vector2f(spaceOcuped));
        return &iceFloor2;
    case PurpleFloor:
        rect.setSize(sf::Vector2f(48, 48));
        rect.setPosition(sf::Vector2f(spaceOcuped));
        return &purpleFloor;

    default:
        return NULL;
    }
}