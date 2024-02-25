#ifndef ARDUINO_ABSTRACTION_ARDUINO_H
#define ARDUINO_ABSTRACTION_ARDUINO_H
#include <cinttypes>
#include "core_pins.h"
#include "pins_arduino.h"
uint32_t millis(void);
unsigned long micros();
#include "elapsedMillis.h"
#include <math.h>
#ifndef _MSC_VER
typedef unsigned char byte;
typedef unsigned short int word;
typedef bool boolean;
#else
#endif
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

// WMath.cpp
long map(long, long, long, long, long);
#define PROGMEM
#define DMAMEM
#define FLASHMEM
#define EXTMEM
#define FASTRUN
#define interrupts()
#define noInterrupts()

void initialize_mock_arduino();

typedef void (*myyieldfn)();
extern myyieldfn yield_impl;

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

#ifndef HALF_PI
#define HALF_PI 1.5707963267948966192313216916398
#endif

#ifndef TWO_PI
#define TWO_PI 6.283185307179586476925286766559
#endif

void __disable_irq();
void __enable_irq();
extern volatile bool arduino_should_exit;
#include "hardware_serial.h"

#ifdef BUILD_SHARED_LIBRARY
void setup() asm("_setup");
void loop() asm("_loop");
#endif
#endif