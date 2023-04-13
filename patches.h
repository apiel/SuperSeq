#ifndef _PATCHES_H_
#define _PATCHES_H_

#include "string.h"

#include "def.h"

class Patch
{
public:
    char name[PATCH_NAME_LEN];
};

Patch patches[MAX_PATCH];


// ./sendosc 127.0.0.1 57123 /patch i 1 s hello
int patch_handler(const char *path, const char *types, lo_arg **argv, int argc, lo_message data, void *user_data)
{
    int id = argv[0]->i;
    Patch& patch = patches[id];

    strncpy(patch.name, &argv[1]->s, PATCH_NAME_LEN);
    log("/patch id:%i name: %s\n", id, patch.name);

    return 0;
}

#endif