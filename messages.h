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
    lo_timetag ts;
    int refcount;
} *lo_msg;

class Message
{
public:
    char *cmd;
    lo_msg msg;
    char *typesOrigin;
    void *dataOrigin;
};
Message messages[MAX_MSG];

void assignArgv(lo_msg msg)
{
    int argc = (int)msg->typelen - 1;
    if (argc)
    {
        msg->argv = (lo_arg **)calloc(argc, sizeof(lo_arg *));
        if (NULL == msg->argv)
        {
            return;
        }
    }
    lo_arg *argv = (lo_arg *)msg->data;
    for (int i = 0; i < argc; i++)
    {
        msg->argv[i] = argv;
        argv = (lo_arg *)((char *)argv + lo_arg_size((lo_type)msg->types[i + 1], argv));
    }
}

// ./sendosc 127.0.0.1 57123 /msg i 1 s /synth s hello i 123 f 0.2
int msg_handler(const char *path, const char *types, lo_arg **argv, int argc, lo_message data, void *user_data)
{
    if (types[0] == LO_INT32 && types[1] == LO_STRING && (&argv[1]->s)[0] == '/')
    {
        int id = argv[0]->i;
        Message &m = messages[id];

        if (m.msg)
        {
            // Reassign pointer address to be able to free them
            m.msg->types = m.typesOrigin;
            m.msg->data = m.dataOrigin;
            lo_message_free(m.msg);
        }

        m.msg = (lo_msg)lo_message_clone(data);
        // Keep track of address to be able to free them later
        m.typesOrigin = m.msg->types;
        m.dataOrigin = m.msg->data;

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

        assignArgv(m.msg);

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

    lo_address targetAddress = lo_message_get_source(data);
    lo_server server = (lo_server)user_data;

    if (!targetAddress)
    {
        return 0;
    }

    int r = lo_send_message_from(targetAddress, server, path, data);

    return 0;
}

// ./sendosc 127.0.0.1 57123 /msg_arg i 1 i 2 f 0.4
int msg_arg_handler(const char *path, const char *types, lo_arg **argv, int argc, lo_message data, void *user_data)
{
    if (types[0] == LO_INT32 && types[1] == LO_INT32)
    {
        int id = argv[0]->i;
        int arg = argv[1]->i;

        Message &m = messages[id];
        if (!m.msg)
        {
            logError("Message[%i] not found\n", id);
            return -1;
        }

        if (types[2] != m.msg->types[arg + 1])
        {
            logError("Invalid type for arg %i. Expected %c, got %c\n", arg, types[2], m.msg->types[arg + 1]);
            return -1;
        }

        memcpy(m.msg->argv[arg], argv[2], lo_arg_size((lo_type)types[2], NULL));

#if DEBUG
        log("Arg value: ");
        lo_arg_pp((lo_type)types[2], m.msg->argv[arg]);
        log("\n");
#endif
    }
    return -1;
}

#endif