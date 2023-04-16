#ifndef _STATE_H_
#define _STATE_H_

#include "def.h"

class Step
{
public:
    uint8_t note;
    uint8_t velocity;
    int duration; // ms
    uint8_t condition;
    uint16_t msgId;
};

class Sequence
{
public:
    int repeat;
    int stepCount;
    Step steps[MAX_STEP];
};

Sequence sequences[MAX_SEQ];

typedef struct _lo_message
{
    char *types;
    size_t typelen;
    size_t typesize;
    void *data;
    size_t datalen;
    size_t datasize;
    lo_address source;
    lo_arg **argv;
    lo_timetag ts;
    int refcount;
} *lo_msg;

class Message
{
public:
    char *cmd;
    int8_t config;
    lo_msg msg;
    char *typesOrigin;
    void *dataOrigin;
};
Message messages[MAX_MSG];

// counter goes from 0 to 65535 (0xFFFF)
uint16_t beatCounter = 0;

#endif