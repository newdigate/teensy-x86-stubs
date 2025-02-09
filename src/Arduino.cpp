
#include "Arduino.h"
#ifndef _MSC_VER
#include <unistd.h>
#endif

#include <chrono>
#include <thread>
#include <mutex>

unsigned t_start = 0;
unsigned tv_start_unsigned = 0;

bool has_initialized_mock_arduino = false;
using namespace std::chrono;
uint8_t external_psram_size = 16;
uint8_t yield_active_check_flags;
extern "C" { 
    volatile uint32_t systick_millis_count;
    volatile uint32_t systick_cycle_count;
}

/// @brief reset the timer so when calling millis(), etc, you will get the time relative to the start of the program
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
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        //usleep(1000);
    if (yield_active_check_flags & YIELD_CHECK_EVENT_RESPONDER)
        EventResponder_runFromYield();
}

std::mutex critical_section_mutex;
volatile bool arduino_should_exit = false;
void __disable_irq() {
    if (arduino_should_exit) return;    
    while (!critical_section_mutex.try_lock() && !arduino_should_exit) {
        if (arduino_should_exit) return;
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    };
}
void __enable_irq() {
    if (arduino_should_exit) return;
    critical_section_mutex.unlock();
}