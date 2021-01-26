#pragma once

typedef unsigned char byte;
typedef unsigned short int word;
typedef bool boolean;

unsigned long millis();
unsigned long micros();
void delay(unsigned long ms);

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

// WMath.cpp
long map(long, long, long, long, long);

void initialize_mock_arduino(); 

#include "hardware_serial.h"
