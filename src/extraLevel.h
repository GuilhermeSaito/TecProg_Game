#include "phaseMap4.h"
#include "bossThread.h"

#pragma once

class ExtraLevel : public PhaseMap::PhaseMap4
{
private:
    int event_id;
    vector<BossThread*> threadBosses;

public:

};