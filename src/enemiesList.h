#include "enemyEntity.h"
#include "listManager.h"
#include "player1.h"

#pragma once

class EnemiesList
{
private:
    ListElement<Entidade::EnemyEntity> enemiesList;

public:
    EnemiesList();
    ~EnemiesList();

    void include(Entidade::EnemyEntity* e);
    void kill(Element<Entidade::EnemyEntity>* e);
    void setNull();

    void update(Entidade::Player::Player1* p);
    void render(sf::RenderWindow& window);

    Element<Entidade::EnemyEntity>* getFirst();
    const bool isEmpty() const;
    const int getQuantity() const;
};