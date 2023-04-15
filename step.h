#ifndef _STEP_H_
#define _STEP_H_

#include "def.h"
#include "state.h"

// ./sendosc 127.0.0.1 57123 /step i 1 i 0 i 60 i 127 i 1000 i 0 i 0
int step_handler(const char *path, const char *types, lo_arg **argv, int argc, lo_message data, void *user_data)
{
    int seqId = argv[0]->i;
    int stepId = argv[1]->i;

    if (!isValidSeqId(seqId) || !isValidStepId(stepId))
    {
        return -1;
    }

    Step &step = sequences[seqId].steps[stepId];
    step.note = argv[2]->i;
    step.velocity = argv[3]->i;
    step.duration = argv[4]->i;
    step.condition = argv[5]->i;
    step.msgId = argv[6]->i % MAX_MSG;

#if DEBUG
    log("/step seqId:%i, stepId:%i, note:%i, velocity:%i, duration:%i, condition:%i, msgId:%i\n", seqId, stepId, step.note, step.velocity, step.duration, step.condition, step.msgId);
#endif

    return 0;
}

#endif