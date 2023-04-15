#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "def.h"

// config file https://www.walletfox.com/course/parseconfigfile.php#
// or https://github.com/brofield/simpleini
// or maybe just use env var...

const char *port = "57123";

class StepConfig
{
public:
    int8_t noteTarget;
    int8_t freqTarget;
    int8_t velocityTarget;
    int8_t durationTarget;

    StepConfig(int8_t noteTarget, int8_t freqTarget, int8_t velocityTarget, int8_t durationTarget)
        : noteTarget(noteTarget),
          freqTarget(freqTarget),
          velocityTarget(velocityTarget),
          durationTarget(durationTarget) {}
};

StepConfig stepConfigs[MAX_STEP_CONFIG] = {
    {-1, 2, 4, 6},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
};

#endif