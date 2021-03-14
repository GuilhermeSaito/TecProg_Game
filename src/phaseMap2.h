#pragma once

#include "phaseMapGeneral.h"

namespace PhaseMap
{
	class PhaseMap2 : public PhaseMapGeneral
	{
	public:
		PhaseMap2(std::string path = "");
		~PhaseMap2();

		void update(int& controller) override;
		void render(sf::RenderWindow& window, int& controller) override;

	private:
		virtual void renderPhaseBackGround(sf::RenderWindow& window);
	};
}