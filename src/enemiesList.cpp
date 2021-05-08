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
    if (e->getInfo()->getHasProjectiles())
        e->getInfo()->setHasProjectiles(false);

    this->enemiesList.kill(e);
}
void EnemiesList::setNull()
{
    Element<Entidade::EnemyEntity>* aux = this->enemiesList.getFirst();
    while (aux != NULL)
    {
        if (aux->getInfo()->getHasProjectiles())
            aux->getInfo()->getProjectiles()->setNull();
    }
    
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