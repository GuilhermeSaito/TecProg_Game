#pragma once

#include "phaseMapGeneral.h"
#include "listManager.h"

namespace PhaseMap
{
	class PhaseMap3 : public PhaseMapGeneral
	{
	public:
		PhaseMap3(std::string path = "");
		~PhaseMap3();

		void update(int& controller) override;
		void render(sf::RenderWindow& window, int& controller) override;

		void placingEnemies();

	private:
		virtual void renderPhaseBackGround(sf::RenderWindow& window);
	};
}