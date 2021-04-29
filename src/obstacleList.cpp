#include "obstacleList.h"

using namespace Lists;

ObstacleList::ObstacleList()
{
}

ObstacleList::~ObstacleList()
{
}

void ObstacleList::include(Entidade::EnemyEntity *e)
{
    this->obstacleList.include(e);
}
void ObstacleList::kill(Element<Entidade::EnemyEntity> *e)
{
    this->obstacleList.kill(e);
}
void ObstacleList::setNull()
{
    this->obstacleList.setNull();
}

void ObstacleList::update(Entidade::Player::Player1 *p)
{
    this->obstacleList.update(p);
}
void ObstacleList::render()
{
    this->obstacleList.render();
}

Element<Entidade::EnemyEntity> *ObstacleList::getFirst()
{
    return this->obstacleList.getFirst();
}

const bool ObstacleList::isEmpty() const { return (this->obstacleList.isEmpty()); }
const int ObstacleList::getQuantity() const { return this->obstacleList.getQuantity(); }