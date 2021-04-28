#pragma once

#include "phaseMapGeneral.h"
#include "listManager.h"

namespace PhaseMap
{
	class PhaseMap4 : public PhaseMapGeneral
	{
	private:
		sf::Texture deathPhaseBackGround;
		sf::Clock clock;
		sf::Time elapsed;

	public:
		PhaseMap4(sf::RenderWindow *window = NULL, std::string path = "");
		~PhaseMap4();

		void update(int &controller) override;
		void render(int &controller) override;

		void placingEnemies();

		void resetClock();

	private:
		virtual void renderPhaseBackGround();
	};
}