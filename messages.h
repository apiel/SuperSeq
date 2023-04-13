#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#include "string.h"

#include "def.h"

lo_message messages[MAX_PATCH];

// ./sendosc 127.0.0.1 57123 /msg i 1 s /synth s hello i 123 f 0.2
int msg_handler(const char *path, const char *types, lo_arg **argv, int argc, lo_message data, void *user_data)
{
    if (types[0] == LO_INT32 && types[1] == LO_STRING && (&argv[1]->s)[0] == '/')
    {
        int id = argv[0]->i;
        messages[id] = lo_message_clone(data);
        
#if DEBUG    
        log("Save message[%i]", id);    
        lo_message_pp(data);
#endif
        return 0;
    } else {
        logError("\nInvalid message format.\n  Expecing /msg is... id /cmd ...args\n  e.g.: /msg issf 1 /synth cutoff 2000.0\n\n");
        return -1;
    }
    return -1;
}

#endif