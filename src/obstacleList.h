#pragma once

#include "enemyEntity.h"
#include "listManager.h"
#include "player1.h"

namespace Lists
{
    class ObstacleList
    {
    private:
        ListElement<Entidade::EnemyEntity> obstacleList;

    public:
        ObstacleList();
        ~ObstacleList();
        //todas as funções foram feitas apenas para chamar as iguais da lista template
        void include(Entidade::EnemyEntity *o);
        void kill(Element<Entidade::EnemyEntity> *o);
        void setNull();

        void update(Entidade::Player::Player1 *p);
        void render();

        Element<Entidade::EnemyEntity> *getFirst();
        const bool isEmpty() const;
        const int getQuantity() const;
    };
}