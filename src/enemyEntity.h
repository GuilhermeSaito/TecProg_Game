#pragma once

#include "entity.h"

namespace Entidade
{
	class EnemyEntity: public Entity
	{
	protected:
		bool canHitPlayer1;
		bool canHitPlayer2;
		bool isDead;

		int attackDamage = 0;

	public:
		EnemyEntity(sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attack = 0);
		virtual ~EnemyEntity();

		virtual void timerCanHitPlayer();
		const bool getCanHitPlayer1() const;
		const bool getCanHitPlayer2() const;

		const bool getIsDead() const;
		void setIsDead(const bool dead);

		void setAttackDamage(int attack);
		int getAttackDamage();

		void render(sf::RenderWindow& window);
	};
}
