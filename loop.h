#ifndef _LOOP_H_
#define _LOOP_H_

#include <chrono>
#include "def.h"

auto last = std::chrono::steady_clock::now();

uint16_t bpm = 120;

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

    if (elapsed_seconds.count() >= quaterBeatSec) {
        last = now;
        printf("elapsed time: %.1f ms\n", elapsed_seconds.count() * 1000);
    }
}

#endif