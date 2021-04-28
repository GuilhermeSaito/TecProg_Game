#pragma once

#include "phaseMapGeneral.h"

namespace PhaseMap
{
	class PhaseMap2 : public PhaseMapGeneral
	{
	private:
		sf::Texture blueOceanPhaseBackGround;

	public:
		PhaseMap2(sf::RenderWindow *window = NULL, std::string path = "");
		~PhaseMap2();

		void update(int &controller) override;
		void render(int &controller) override;

		void placingEnemies();

	private:
		virtual void renderPhaseBackGround();
	};
}