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

    // nextToPlay, triggerSeq?, starting in???
    // bool playing;
    // int steps[4][1][4];
};

Sequence sequences[MAX_SEQ];


// ./sendosc 127.0.0.1 57123 /seq i 1 i 2 i 16
int seq_handler(const char *path, const char *types, lo_arg **argv, int argc, lo_message data, void *user_data)
{
    int id = argv[0]->i;
    Sequence& seq = sequences[id];
    seq.repeat = argv[1]->i;
    seq.stepCount = argv[2]->i;

    log("/seq id:%i, repeat:%i, stepCount:%i\n", id, seq.repeat, seq.stepCount);

    return 0;
}

#endif