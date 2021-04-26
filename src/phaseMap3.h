#pragma once

#include "phaseMapGeneral.h"
#include "listManager.h"

namespace PhaseMap
{
	class PhaseMap3 : public PhaseMapGeneral
	{
	public:
		PhaseMap3(sf::RenderWindow *window = NULL, std::string path = "");
		~PhaseMap3();

		void update(int &controller) override;
		void render(int &controller) override;

		void placingEnemies();

	private:
		virtual void renderPhaseBackGround();
	};
}