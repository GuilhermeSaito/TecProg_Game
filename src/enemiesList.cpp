#include "enemiesList.h"

using namespace Lists;

EnemiesList::EnemiesList()
{
}

EnemiesList::~EnemiesList()
{
}

void EnemiesList::include(Entidade::EnemyEntity *e)
{
    this->enemiesList.include(e);
}
void EnemiesList::kill(Element<Entidade::EnemyEntity> *e)
{
    this->enemiesList.kill(e);
}
void EnemiesList::setNull()
{
    this->enemiesList.setNull();
}

void EnemiesList::update(Entidade::Player::Player1 *p)
{
    this->enemiesList.update(p);
}
void EnemiesList::render()
{
    this->enemiesList.render();
}

Element<Entidade::EnemyEntity> *EnemiesList::getFirst()
{
    return this->enemiesList.getFirst();
}

const bool EnemiesList::isEmpty() const { return (this->enemiesList.isEmpty()); }
const int EnemiesList::getQuantity() const { return this->enemiesList.getQuantity(); }