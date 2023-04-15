#ifndef _SEQ_H_
#define _SEQ_H_

#include "def.h"
#include "state.h"

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

#endif