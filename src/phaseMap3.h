#pragma once

#include "phaseMapGeneral.h"

namespace PhaseMap
{
	class PhaseMap3 : public PhaseMapGeneral
	{
	public:
		PhaseMap3(std::string path = "");
		~PhaseMap3();

		void update(int& controller) override;
		void render(sf::RenderWindow& window, int& controller) override;

	private:
		virtual void renderPhaseBackGround(sf::RenderWindow& window);
	};
}