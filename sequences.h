#ifndef _SEQUENCES_H_
#define _SEQUENCES_H_

#include "def.h"

class Step
{
public:
    uint8_t note;
    uint8_t velocity;
    int duration; // ms or ticks? but duration need to be passed to the synth or?
    uint8_t condition;
    uint16_t msgId;

    // uint16_t endMsgId; // should there be a end message when duration reached? : NOPE
    // but there could be a glolbal parameter to set a message for end duration, however
    // this would mean that have to keep track of nodeId...
};

class Sequence
{
public:
    int repeat;
    int stepCount;
    Step steps[MAX_STEP];
};

Sequence sequences[MAX_SEQ];

// ./sendosc 127.0.0.1 57123 /seq i 1 i 2 i 16
int seq_handler(const char *path, const char *types, lo_arg **argv, int argc, lo_message data, void *user_data)
{
    int id = argv[0]->i;

    if (!isValidSeqId(id))
    {
        return -1;
    }

    Sequence &seq = sequences[id];
    seq.repeat = argv[1]->i;
    seq.stepCount = argv[2]->i;

#if DEBUG
    log("/seq id:%i, repeat:%i, stepCount:%i\n", id, seq.repeat, seq.stepCount);
#endif

    return 0;
}

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