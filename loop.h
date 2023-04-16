#ifndef _LOOP_H_
#define _LOOP_H_

#include <chrono>
#include "def.h"

auto last = std::chrono::steady_clock::now();

uint16_t bpm = 120;

lo_address targetAddress;

float getQuaterBeatSec()
{
    // There is 4 quater per beat
    // return 60.0f / bpm / 4.0f;
    return 15.0f / bpm;
}

float quaterBeatSec = getQuaterBeatSec();

void loop(lo_server server)
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - last;

    if (elapsed_seconds.count() >= quaterBeatSec)
    {
        last = now;
        // printf("elapsed time: %.1f ms\n", elapsed_seconds.count() * 1000);
        if (targetAddress)
        {
            // lo_send_message_from(targetAddress, server, "/beat", data);
            // lo_send(targetAddress, "/beat", "i", counter);
            lo_send(targetAddress, "/beat", "");
        }
    }
}

// ./sendosc 127.0.0.1 57123 /sub
int sub_handler(const char *path, const char *types, lo_arg **argv, int argc, lo_message data, void *user_data)
{
    targetAddress = lo_message_get_source(data);

#if DEBUG
    log("Subscribe to /beat\n");
#endif

    return 0;
}

#endif