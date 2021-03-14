#pragma once

#include "phaseMapGeneral.h"

namespace PhaseMap
{
	class PhaseMap4 : public PhaseMapGeneral
	{
	public:
		PhaseMap4(std::string path = "");
		~PhaseMap4();

		void update(int& controller) override;
		void render(sf::RenderWindow& window, int& controller) override;

	private:
		virtual void renderPhaseBackGround(sf::RenderWindow& window);
	};
}