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

#ifndef CorePins_h
#define CorePins_h

#define HIGH			1
#define LOW			0
#define INPUT			0
#define OUTPUT			1
#define INPUT_PULLUP		2
#define INPUT_PULLDOWN		3
#define OUTPUT_OPENDRAIN	4
#define INPUT_DISABLE		5
#define LSBFIRST		0
#define MSBFIRST		1
#define _BV(n)			(1<<(n))
#define CHANGE			4
#define FALLING			2
#define RISING			3

#include "Arduino.h"

void digitalWrite(uint8_t pin, uint8_t val);
inline void digitalWriteFast(uint8_t pin, uint8_t val);
uint8_t digitalRead(uint8_t pin);
inline uint8_t digitalReadFast(uint8_t pin);
void digitalToggle(uint8_t pin);
inline void digitalToggleFast(uint8_t pin);
void pinMode(uint8_t pin, uint8_t mode);
void init_pins(void);
void analogWrite(uint8_t pin, int val);
uint32_t analogWriteRes(uint32_t bits);
inline uint32_t analogWriteResolution(uint32_t bits);
void analogWriteFrequency(uint8_t pin, float frequency);
void attachInterrupt(uint8_t pin, void (*function)(void), int mode);
void detachInterrupt(uint8_t pin);
void _init_Teensyduino_internal_(void);
int analogRead(uint8_t pin);
void analogReference(uint8_t type);
void analogReadRes(unsigned int bits);
inline void analogReadResolution(unsigned int bits);
void analogReadAveraging(unsigned int num);
void analog_init(void);
int touchRead(uint8_t pin);

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
void _reboot_Teensyduino_(void) __attribute__((noreturn));
void _restart_Teensyduino_(void) __attribute__((noreturn));

void yield(void);

uint32_t millis(void);

void delayMilliseconds(uint32_t millisec);

void delay(uint32_t msec);

unsigned long micros();

void delayMicroseconds(uint32_t usec);

unsigned long nanos();

void delayNanoseconds(uint32_t nsec);

unsigned long rtc_get(void);
void rtc_set(unsigned long t);
void rtc_compensate(int adjust);

void tempmon_init(void);
float tempmonGetTemp(void);
void tempmon_Start();
void tempmon_Stop();
void tempmon_PwrDwn();

#define constrain(amt, low, high) ({ \
  typeof(amt) _amt = (amt); \
  typeof(low) _low = (low); \
  typeof(high) _high = (high); \
  (_amt < _low) ? _low : ((_amt > _high) ? _high : _amt); \
})

#endif