
#include "Arduino.h"
#include <unistd.h>
#include <chrono>
#include <thread>
#include <mutex>
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
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        //usleep(1000);
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