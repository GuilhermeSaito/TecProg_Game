#include "phaseMapGeneral.h"
#include "threadedBoss.h"

#pragma once

namespace PhaseMap
{
    class ExtraLevel: public PhaseMapGeneral 
    {
    private:
        sf::Texture lastPhaseBackGround;
        sf::Clock clock;
		sf::Time elapsed;

        int event_id;
        vector<Thread::ThreadedBoss*> threadedBosses;

    public:
        ExtraLevel(sf::RenderWindow *window = NULL, std::string path = "");
        ~ExtraLevel();

		void update(int &controller) override;
		void render(int &controller) override;

	private:
		void placingEnemies() override;
		void placingObstacles() override;

		void renderPhaseBackGround();
        void resetClock();
    };
}