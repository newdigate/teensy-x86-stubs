
#include "Arduino.h"
#include <unistd.h>
#include <chrono>
unsigned long t_start;
unsigned tv_start_unsigned;

bool has_initialized_mock_arduino = false;
using namespace std::chrono;
void initialize_mock_arduino() {
    if (!has_initialized_mock_arduino) {

        auto epoch = system_clock::now().time_since_epoch();

        milliseconds ms = duration_cast< milliseconds >(epoch);
        t_start = ms.count();

        microseconds us = duration_cast< microseconds >(epoch);
        tv_start_unsigned = us.count();

        has_initialized_mock_arduino = true;
    }
}

myyieldfn yield_impl = NULL;
void yield()
{
    if (yield_impl)
        yield_impl();
    else
        usleep(1000);
}

void __disable_irq() {}
void __enable_irq() {}