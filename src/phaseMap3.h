#pragma once

#include "phaseMapGeneral.h"
#include "listManager.h"

namespace PhaseMap
{
	class PhaseMap3 : public PhaseMapGeneral
	{
	private:
		sf::Texture cavePhaseBackGround;

	public:
		PhaseMap3(sf::RenderWindow *window = NULL, std::string path = "");
		~PhaseMap3();

		void update(int &controller) override;
		void render(int &controller) override;

	private:
		void placingEnemies() override;
		void placingObstacles() override;

		void renderPhaseBackGround();
	};
}