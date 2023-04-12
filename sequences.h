#ifndef _SEQUENCES_H_
#define _SEQUENCES_H_

#include "def.h"

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


// TODO Should it be add or simply edit since seq number should be fixed!
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