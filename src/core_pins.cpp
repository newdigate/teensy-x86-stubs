/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2018 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "core_pins.h"
#include <sys/timeb.h>
#include <sys/time.h>

void digitalWrite(uint8_t pin, uint8_t val) {}
void digitalWriteFast(uint8_t pin, uint8_t val)
{
    digitalWrite(pin, val);
}

uint8_t digitalRead(uint8_t pin) {}
uint8_t digitalReadFast(uint8_t pin)
{
    return 0;
}

void digitalToggle(uint8_t pin) {}
void digitalToggleFast(uint8_t pin)
{
    digitalToggle(pin);
}

void pinMode(uint8_t pin, uint8_t mode) {}
void init_pins(void) {}
void analogWrite(uint8_t pin, int val) {}
uint32_t analogWriteRes(uint32_t bits) {return 0;}
inline uint32_t analogWriteResolution(uint32_t bits) { return analogWriteRes(bits); }
void analogWriteFrequency(uint8_t pin, float frequency) {}
void attachInterrupt(uint8_t pin, void (*function)(void), int mode) {}
void detachInterrupt(uint8_t pin) {}
void _init_Teensyduino_internal_(void) {}
int analogRead(uint8_t pin) {return 0;}
void analogReference(uint8_t type) {}
void analogReadRes(unsigned int bits) {}
inline void analogReadResolution(unsigned int bits) { analogReadRes(bits); }
void analogReadAveraging(unsigned int num) {}
void analog_init(void) {}
int touchRead(uint8_t pin) {}

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value)
{
}

uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder)
{
}

void _reboot_Teensyduino_(void) __attribute__((noreturn));
void _restart_Teensyduino_(void) __attribute__((noreturn));

void yield(void);

extern timeb t_start;
extern unsigned tv_start_unsigned;

uint32_t millis(void) {
    timeb t_now;
    ftime(&t_now);
    return (t_now.time  - t_start.time) * 1000 + (t_now.millitm - t_start.millitm);
}

void delayMilliseconds(uint32_t millisec)
{
    unsigned long start = millis();
    while(millis() - start < millisec){
        yield();
    }
}

void delay(uint32_t msec) {
    delayMilliseconds(msec);
}


unsigned long micros() {
    struct timeval tv_now;
    gettimeofday(&tv_now,NULL);
    unsigned long time_in_micros = 1000000 * tv_now.tv_sec + tv_now.tv_usec;
    return (time_in_micros - tv_start_unsigned);
}

void delayMicroseconds(uint32_t usec)
{
    unsigned long start = micros();
    while(micros() - start < usec){
        yield();
    }
}

unsigned long nanos() {
    struct timeval tv_now;
    gettimeofday(&tv_now,NULL);
    unsigned long time_in_micros = 1000000000 * tv_now.tv_sec + tv_now.tv_usec;
    return (time_in_micros - tv_start_unsigned);
}

void delayNanoseconds(uint32_t nsec)
{
    unsigned long start = nanos();
    while(nanos() - start < nsec){
        yield();
    }
}


unsigned long rtc_get(void) { return millis(); }
void rtc_set(unsigned long t) {}
void rtc_compensate(int adjust) {}

void tempmon_init(void) {}
float tempmonGetTemp(void) {}
void tempmon_Start() {}
void tempmon_Stop() {}
void tempmon_PwrDwn() {}

