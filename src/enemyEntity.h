#pragma once

#include "entity.h"
#include "listManager.h"
#include "projectilesList.h"
#include "player1.h"

namespace Entidade
{
	class EnemyEntity : public Entity
	{
	protected:
		bool canHitPlayer1;
		bool canHitPlayer2;
		bool isDead;
		bool hasProjectiles;

	public:
		EnemyEntity(sf::RenderWindow *window = NULL, sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attack = 0, const int point = 0);
		virtual ~EnemyEntity();

		virtual void timerCanHitPlayer();
		const bool getCanHitPlayer1() const;
		const bool getCanHitPlayer2() const;

		const bool getIsDead() const;
		void setIsDead(const bool dead);

		const bool getHasProjectiles() const;
		void setHasProjectiles(const bool y);

		virtual Lists::ProjectilesList *getProjectiles() = 0;
		virtual void movimentation(sf::Vector2f playerPosition) = 0;
		virtual void update(Entidade::Player::Player1 *p) = 0;
		virtual void render() = 0;
	};
}
