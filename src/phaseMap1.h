#pragma once

#include <vector>

#include "phaseMapGeneral.h"
#include "zombie.h"

namespace PhaseMap
{
	class PhaseMap1 : public PhaseMapGeneral
	{
	private:
		std::vector<Entidade::Enemy::Zombie*> zombieEnemys;

	public:
		PhaseMap1(std::string path = "");
		~PhaseMap1();

		void update(int& controller) override;
		void render(sf::RenderWindow& window, int& controller) override;

	private:
		void renderPhaseBackGround(sf::RenderWindow& window);
		void placingEnemys();
	};
}
