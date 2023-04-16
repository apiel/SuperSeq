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

void loop()
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - last;

    if (elapsed_seconds.count() >= quaterBeatSec)
    {
        last = now;
        // printf("elapsed time: %.1f ms\n", elapsed_seconds.count() * 1000);
        if (targetAddress)
        {
            beatCounter++;
            lo_send(targetAddress, "/beat", "i", beatCounter);
        }
    }
}

// ./sendosc 127.0.0.1 57123 /sub
int sub_handler(const char *path, const char *types, lo_arg **argv, int argc, lo_message data, void *user_data)
{
    lo_address target = lo_message_get_source(data);
    if (targetAddress)
    {
        lo_address_free(targetAddress);
    }
    targetAddress = lo_address_new(lo_address_get_hostname(target), lo_address_get_port(target));


#if DEBUG
    log("Subscribe to /beat\n");
#endif

    return 0;
}

#endif