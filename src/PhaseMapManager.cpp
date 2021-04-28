#include "PhaseMapManager.h"

#include <fstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

using namespace PhaseMap::Tiles;

PhaseMapManager::PhaseMapManager(sf::RenderWindow *window, std::string p) : Menu(window),
                                                                            path(p),
                                                                            alturaMax(0),
                                                                            larguraMax(0)
{
}

PhaseMapManager::~PhaseMapManager()
{
    window = NULL;
    clearMatrix();
}

bool PhaseMapManager::loadMapTileProprieties()
{
    std::ifstream in(path);
    if (!in.good())
    {
        std::cout << "Nao foi possivel abrir o " << path << std::endl;
        return false;
    }
    std::cout << path << "\tLoaded" << std::endl;

    clearMatrix();

    json jMap;
    in >> jMap;

    alturaMax = jMap["height"];
    larguraMax = jMap["width"];

    for (int j = 0; j < alturaMax; j++)
    {
        std::vector<Tile *> tileLinha;
        for (int i = 0; i < larguraMax; i++)
        {
            int tilePropriedade = jMap["layers"][0]["data"][j * larguraMax + i];
            tileLinha.push_back(new Tile(window, tilePropriedade, sf::Vector2f(i * 48, j * 48)));
        }
        tileMap.push_back(tileLinha);
    }
    in.close();

    return true;
}

void PhaseMapManager::draw()
{
    for (std::vector<Tile *> i : tileMap)
        for (Tile *j : i)
            j->draw();
}

std::vector<std::vector<Tile *>> PhaseMapManager::getMatrixTile()
{
    return tileMap;
}

Tile *PhaseMapManager::getTile(int posX, int posY)
{
    return tileMap[posY][posX];
}

bool PhaseMapManager::isValidTile(int i, int j)
{
    if (((i >= 0) && (i <= larguraMax)) && ((j >= 0) && (j <= alturaMax)))
        return true;
    return false;
}

void PhaseMapManager::clearMatrix()
{
    for (std::vector<Tile *> v : tileMap)
        for (Tile *t : v)
            if (t != NULL)
                delete t;
    tileMap.clear();
}