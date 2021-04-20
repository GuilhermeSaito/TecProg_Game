#pragma once

#include <vector>

#include "phaseMapGeneral.h"

namespace PhaseMap
{
	class PhaseMap1 : public PhaseMapGeneral
	{
	public:
		PhaseMap1(std::string path = "");
		~PhaseMap1();

		void update(int& controller) override;
		void render(sf::RenderWindow& window, int& controller) override;

		void renderPhaseBackGround(sf::RenderWindow& window);
		void placingEnemies();
	};
}
