#pragma once

#include "phaseMapGeneral.h"

namespace PhaseMap
{
	class PhaseMap2 : public PhaseMapGeneral
	{
	private:
		ListElement<Entidade::Enemy::Zombie> zombiesList;
		ListElement<Entidade::Enemy::GoblinMage> goblinMagesList;

	public:
		PhaseMap2(std::string path = "");
		~PhaseMap2();

		void update(int& controller) override;
		void render(sf::RenderWindow& window, int& controller) override;

		void placingEnemies();
		void loadEnemiesListsInCollision();

	private:
		virtual void renderPhaseBackGround(sf::RenderWindow& window);
	};
}