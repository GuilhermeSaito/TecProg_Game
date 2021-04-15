#pragma once

#include "phaseMapGeneral.h"
#include "listManager.h"

namespace PhaseMap
{
	class PhaseMap3 : public PhaseMapGeneral
	{
	private:
		ListElement<Entidade::Enemy::Zombie> zombiesList;
		ListElement<Entidade::Enemy::GoblinMage> goblinMagesList;
		ListElement<Entidade::Enemy::FlyingEnemy> flyingEnemiesList;

	public:
		PhaseMap3(std::string path = "");
		~PhaseMap3();

		void update(int& controller) override;
		void render(sf::RenderWindow& window, int& controller) override;

		void placingEnemies();
		void loadEnemiesListsInCollision();

	private:
		virtual void renderPhaseBackGround(sf::RenderWindow& window);
	};
}