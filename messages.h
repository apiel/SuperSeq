#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#include "string.h"

#include "def.h"

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
    /* timestamp from bundle (LO_TT_IMMEDIATE for unbundled messages) */
    lo_timetag ts;
    int refcount;
} *lo_msg;

class Message
{
public:
    char * cmd;
    lo_msg msg;
};
// If we want to store the string, we need to keep track of the length???
Message messages[MAX_MSG];

// ./sendosc 127.0.0.1 57123 /msg i 1 s /synth s hello i 123 f 0.2
int msg_handler(const char *path, const char *types, lo_arg **argv, int argc, lo_message data, void *user_data)
{
    if (types[0] == LO_INT32 && types[1] == LO_STRING && (&argv[1]->s)[0] == '/')
    {
        int id = argv[0]->i;
        Message &m = messages[id];
        m.msg = (lo_msg)lo_message_clone(data);

        // remove first 2 types
        m.msg->types += 2;
        m.msg->typelen -= 2;
        m.msg->types[0] = ',';
        // remove first 2 args
        int len = lo_arg_size(LO_INT32, NULL);
        m.msg->data = (char *)m.msg->data + len;
        m.cmd = (char *)m.msg->data;
        int len2 = lo_arg_size(LO_STRING, m.msg->data);
        m.msg->data = (char *)m.msg->data + len2;
        m.msg->datalen -= (len + len2);

#if DEBUG
        log("Save message[%i]", id);
        lo_message_pp(data);
#endif
        return 0;
    }
    else
    {
        logError("\nInvalid message format.\n  Expecing /msg is... id /cmd ...args\n  e.g.: /msg issf 1 /synth cutoff 2000.0\n\n");
        return -1;
    }
    return -1;
}

// ./sendosc 127.0.0.1 57123 /msg_get i 1
int msg_get_handler(const char *path, const char *types, lo_arg **argv, int argc, lo_message data, void *user_data)
{
    int id = argv[0]->i;
    log("Message[%i] %s ", id, messages[id].cmd);
    lo_message_pp(messages[id].msg);

    // should send to client
    // lo_send(t, "/s_new", "si", "psykick", 2000);??
    return 0;
}

// ./sendosc 127.0.0.1 57123 /msg_arg i 1 i 4 f 0.4
int msg_arg_handler(const char *path, const char *types, lo_arg **argv, int argc, lo_message data, void *user_data)
{
    if (types[0] == LO_INT32 && types[1] == LO_INT32)
    {
        int id = argv[0]->i;
        int arg = argv[1]->i;

        // messages[id]->argv[arg] = argv[2];

        // memcpy(messages[id]->argv[arg], argv[2], sizeof(lo_arg));

        // printf("argv[%i] = %f\n", arg, messages[id]->argv[arg]->f);
        // lo_arg_pp((lo_type)messages[id]->types[arg], messages[id]->argv[arg]);

        // lo_arg_pp(LO_FLOAT, messages[id]);

        // need to find the position of the args using types sizes...
    }
    return -1;
}

#endif