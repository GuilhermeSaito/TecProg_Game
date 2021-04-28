#include "projectilesList.h"
using namespace Lists;

ProjectilesList::ProjectilesList()
{
}

ProjectilesList::~ProjectilesList()
{
}

void ProjectilesList::include(Projectile *e)
{
    this->projectilesList.include(e);
}
void ProjectilesList::kill(Element<Projectile> *e)
{
    this->projectilesList.kill(e);
}
void ProjectilesList::setNull()
{
    this->projectilesList.setNull();
}

void ProjectilesList::update(Entidade::Player::Player1 *p)
{
    this->projectilesList.update(p);
}
void ProjectilesList::render()
{
    this->projectilesList.render();
}

Element<Projectile> *ProjectilesList::getFirst()
{
    return this->projectilesList.getFirst();
}

const bool ProjectilesList::isEmpty() const { return (this->projectilesList.isEmpty()); }
const int ProjectilesList::getQuantity() const { return this->projectilesList.getQuantity(); }
void ProjectilesList::setQuantity(int i) { this->projectilesList.setQuantity(i); }
