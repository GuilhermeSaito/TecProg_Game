#pragma once

#include <vector>

#include "phaseMapGeneral.h"

namespace PhaseMap
{
	class PhaseMap1 : public PhaseMapGeneral
	{
	private:
		sf::Texture beginnerPhaseBackGround;

	public:
		PhaseMap1(sf::RenderWindow *window = NULL, std::string path = "");
		~PhaseMap1();

		void update(int &controller) override;
		void render(int &controller) override;

		void renderPhaseBackGround();
		void placingEnemies();
	};
}
