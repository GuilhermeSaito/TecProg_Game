#include "projectile.h"
#include "listManager.h"
#include "player1.h"

#pragma once
//Classe que lida com a lista de prjéteis da classe template
namespace Lists
{
    class ProjectilesList
    {
    private:
        ListElement<Projectile> projectilesList;

    public:
        //Todas as funções são apenas feitas para chamar as iguais porém na classe template
        ProjectilesList();
        ~ProjectilesList();

        void include(Projectile *e);
        void kill(Element<Projectile> *e);
        void setNull();

        void update(Entidade::Player::Player1 *p);
        void render();

        Element<Projectile> *getFirst();
        const bool isEmpty() const;
        const int getQuantity() const;
        void setQuantity(int i);
    };
}