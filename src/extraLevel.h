#include "phaseMapGeneral.h"
#include "threadedBoss.h"

#pragma once

namespace PhaseMap
{
    class ExtraLevel : public PhaseMapGeneral
    {
    private:
        sf::Texture lastPhaseBackGround;
        sf::Clock clock;
        sf::Time elapsed;

        int event_id;
        Tred::ThreadedBoss *threadedBosses;

    public:
        ExtraLevel(sf::RenderWindow *window = NULL, std::string path = "");
        ~ExtraLevel();

        void update(int &controller) override;
        void render(int &controller) override;

        // Metodo proprio para setar os players e inicializar a thread
        void setSpecialPlayer1(Entidade::Player::Player1 *p1);
        void setSpecialPlayer2(Entidade::Player::Player2 *p2);

    private:
        void placingEnemies() override;
        void placingObstacles() override;

        void renderPhaseBackGround();
        void resetClock();
    };
}