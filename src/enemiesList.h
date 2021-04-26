#include "enemyEntity.h"
#include "listManager.h"
#include "player1.h"

#pragma once
//classe que lida com as lista de inimigos proveniente da lista template
class EnemiesList
{
private:
    ListElement<Entidade::EnemyEntity> enemiesList;

public:
    EnemiesList();
    ~EnemiesList();
    //todas as funções foram feitas apenas para chamar as iguais da lista template
    void include(Entidade::EnemyEntity *e);
    void kill(Element<Entidade::EnemyEntity> *e);
    void setNull();

    void update(Entidade::Player::Player1 *p);
    void render();

    Element<Entidade::EnemyEntity> *getFirst();
    const bool isEmpty() const;
    const int getQuantity() const;
};