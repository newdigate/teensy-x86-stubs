/*
  DSM2_tx implements the serial communication protocol used for operating
  the RF modules that can be found in many DSM2-compatible transmitters.

  Copyrigt (C) 2012  Erik Elmore <erik@ironsavior.net>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.  
*/

#include <cstring>
#include <iostream>
#include <cstdio>      // perror(), stderr, stdin, fileno()
#include <cstdarg>
#ifndef _MSC_VER
#include <termios.h>
#include <sys/ioctl.h>
#else
#include <Windows.h>
#include <conio.h>
#endif
#include "hardware_serial.h"

int kbhit(void) {
#ifndef _MSC_VER
    static bool initflag = false;
    static const int STDIN = 0;
    if (!initflag) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initflag = true;
    }

    int nbbytes = 0;
    ioctl(STDIN, FIONREAD, &nbbytes);  // 0 is STDIN
    return nbbytes;
#else
    int nbbytes = 0;
    nbbytes =_kbhit();
    return nbbytes;
#endif
}

void HardwareSerial::InitializeConsole() {
#ifdef _MSC_VER
    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hstdin, &_consoleMode);
    SetConsoleMode(hstdin, 0);
#endif
}

void  HardwareSerial::ResetConsole() {
#ifdef _MSC_VER
    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hstdin, _consoleMode);
#endif
}

void HardwareSerial::begin(unsigned long speed) {
    // Set terminal to single character mode.

    return;
}

void HardwareSerial::end() {
  return;
}

int HardwareSerial::available(void) {
    return !input.empty() || kbhit();
}

void HardwareSerial::begin(unsigned long, uint8_t) {

}

int HardwareSerial::peek(void) {
  return std::cin.peek();
}

int HardwareSerial::read(void) {
    if (!input.empty()){
      char &c = input.front();
      input.pop();
      return c;
    }
#ifndef _MSC_VER
    if (!kbhit())
        return -1;
    char c = getchar();
    return c;
#else
    //char c = getchar();
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[1];
    int counter = 0;
    DWORD bufSize = 0;
    // Get the standard input handle.

    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (!GetNumberOfConsoleInputEvents(hStdin, &bufSize))
        return -1;

    if (bufSize == 0)
        return -1;

    if (!ReadConsoleInput(
        hStdin,      // input buffer handle
        irInBuf,     // buffer to read into
        1,         // size of read buffer
        &cNumRead)) // number of records read
        return -1;
    if (cNumRead == 0) return -1;
    switch (irInBuf[0].EventType)
    {
        case KEY_EVENT: // keyboard input
            if (irInBuf[0].Event.KeyEvent.bKeyDown)
                return irInBuf[0].Event.KeyEvent.uChar.AsciiChar;
            else
                return -1;
        default:
            return -1;
    }
#endif
}

int HardwareSerial::availableForWrite(void) {
  return 0;
}

void HardwareSerial::flush(void) {

}

size_t HardwareSerial::write(uint8_t a) {
    char c = static_cast<char>(a);
    std::cout.write(&c, 1);
    for(auto & callback: callbacks) {
        if (callback) {
            callback(&c, 1);
        }
    }
    return 0;
}
size_t HardwareSerial::write(unsigned char const* value, unsigned long count) {
    auto value2 = reinterpret_cast<const char *>(value);

#ifdef REDIRECT_SERIAL_OUT_TO_STD_OUT
    std::cout.write(value2, count);
#endif

    for(auto & callback: callbacks) {
        if (callback) {
            callback(value2, count);
        }
    }
    return 0;
}
HardwareSerial Serial;
