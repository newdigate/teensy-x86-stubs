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
#include <termios.h>
#include <sys/ioctl.h>
#include "hardware_serial.h"

int kbhit(void) {
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

    int nbbytes;
    ioctl(STDIN, FIONREAD, &nbbytes);  // 0 is STDIN
    return nbbytes;
}

void HardwareSerial::begin(unsigned long speed) {
    // Set terminal to single character mode.

    return;
}

void HardwareSerial::end() {
  return;
}

int HardwareSerial::available(void) {
    return kbhit();
}

void HardwareSerial::begin(unsigned long, uint8_t) {

}

int HardwareSerial::peek(void) {
  return cin.peek();
}

int HardwareSerial::read(void) {
    if (!kbhit())
        return -1;
    char c = getchar();
    return c;
}

int HardwareSerial::availableForWrite(void) {
  return 0;
}

void HardwareSerial::flush(void) {

}

int HardwareSerial::write(uint8_t a) {
  // std::cout << a;
  return 0;
}
int HardwareSerial::write(unsigned char const* value, unsigned long count) {
    cout << value;
    return 0;
}

HardwareSerial Serial;
