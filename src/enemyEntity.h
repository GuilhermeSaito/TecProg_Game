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

	public:
		EnemyEntity(sf::Vector2f pos = { 0 , 0 }, sf::Vector2f spee = { 0, 0 }, float hP = 100, float attack = 10);
		virtual ~EnemyEntity();

		virtual void timerCanHitPlayer();
		const bool getCanHitPlayer1() const;
		const bool getCanHitPlayer2() const;

		const bool getIsDead() const;
		void setIsDead(const bool dead);

		void render(sf::RenderWindow& window);
	};
}
