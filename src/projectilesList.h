#include "projectile.h"
#include "listManager.h"
#include "player1.h"

#pragma once

class ProjectilesList
{
private:
    ListElement<Projectile> projectilesList;

public:
    ProjectilesList();
    ~ProjectilesList();

    void include(Projectile* e);
    void kill(Element<Projectile>* e);
    void setNull();

    void update(Entidade::Player::Player1* p);
    void render(sf::RenderWindow& window);

    Element<Projectile>* getFirst();
    const bool isEmpty() const;
    const int getQuantity() const;
    void setQuantity(int i);
};