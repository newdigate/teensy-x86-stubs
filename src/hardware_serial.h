/*
  HardwareSerial.h - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
*/

#ifndef HardwareSerial_h
#define HardwareSerial_h

#ifndef _MSC_VER
#include <termios.h>    // struct termios, tcgetattr(), tcsetattr()
#endif

#include <queue>
#include "Stream.h"
#include <sstream>

class HardwareSerial : public Stream {
public:
    HardwareSerial() : Stream() {
        InitializeConsole();
    }

    virtual ~HardwareSerial() {
        ResetConsole();
    };

    void InitializeConsole();
    void ResetConsole();
    void begin(unsigned long baud);
    void begin(unsigned long, uint8_t);
    void end();
    int available(void);
    int peek(void);
    int read(void);
    int availableForWrite(void);
    void flush(void);
    size_t write(uint8_t);
    inline int write(unsigned long n) { return write((uint8_t)n); }
    inline int write(long n) { return write((uint8_t)n); }
    inline int write(unsigned int n) { return write((uint8_t)n); }
    inline int write(int n) { return write((uint8_t)n); }
    size_t write(unsigned char const*, unsigned long);
    operator bool() { return true; }

    // non-Arduino api
    void queueSimulatedCharacterInput(char *c, long numChars) {
      for (int i = 0; i<numChars; i++) {
        input.push(c[i]);
      }
    }

    void addEventListener(const std::function<void(const char *, size_t)> &callback) {
        callbacks.push_back(callback);
    }

    template <typename... Args>
    int printf(const char *format, Args... args) {
        auto length = std::snprintf(NULL, 0, format, args... );
        char buffer[length+100];
        std::snprintf(buffer, length+100, format, args... );
        return write((const unsigned char*)buffer, strlen(buffer));
    }

    static void (*serial1_initialized_callback)(HardwareSerial &s);

private:
#ifndef _MSC_VER
    termios t;
    termios t_saved;
#else
    unsigned long _consoleMode;
#endif

    std::queue<char> input;
    std::vector<std::function<void(const char*, size_t)>> callbacks;
};

extern HardwareSerial Serial;
#endif
