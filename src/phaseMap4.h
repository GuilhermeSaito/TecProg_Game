#pragma once

#include "phaseMapGeneral.h"
#include "listManager.h"

namespace PhaseMap
{
	class PhaseMap4 : public PhaseMapGeneral
	{
	private:
		sf::Clock clock;
		sf::Time elapsed;

	public:
		PhaseMap4(std::string path = "");
		~PhaseMap4();

		void update(int& controller) override;
		void render(sf::RenderWindow& window, int& controller) override;

		void placingEnemies();

		void resetClock();

	private:
		virtual void renderPhaseBackGround(sf::RenderWindow& window);
	};
}