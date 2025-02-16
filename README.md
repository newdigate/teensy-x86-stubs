# teensy x86 stubs
[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![CMake](https://img.shields.io/badge/project-CMake-brightgreen.svg?label=built%20with&colorA=555555&colorB=8a8fff&logo=)](CMakelists.txt)
[![CMake](https://github.com/newdigate/teensy-x86-stubs/workflows/CMake/badge.svg)](https://github.com/newdigate/teensy-x86-stubs/actions)
[![basic-test](https://github.com/newdigate/teensy-x86-stubs/actions/workflows/basic-test.yml/badge.svg)](https://github.com/newdigate/teensy-x86-stubs/actions/workflows/basic-test.yml)

stub classes implementing basic arduino/teensy functions for compiling and debuging on your x86/x64 architecture

## eco-system
[sd](https://github.com/newdigate/teensy-x86-sd-stubs)
|
[audio](https://github.com/newdigate/teensy-audio-x86-stubs)
|
[st7735](https://github.com/newdigate/teensy-st7735-linux-stubs)
|
[midi](https://github.com/newdigate/teensy-x86-midi-stubs)
|
[bounce2](https://github.com/newdigate/teensy-x86-bounce2-stubs)
|
[encoder](https://github.com/newdigate/teensy-x86-encoder-stubs)


## quick example
* to initialize the arduino timing library so that millis() will return the duration in milliseconds since the test app has been runnning
``` c++
    initialize_mock_arduino()
```

## main.cpp
```c++
#include <Arduino.h>
IntervalTimer myTimer;

void blinkLED() {
    Serial.printf("BLINK %d\n", 1000);
}

int main(int argc, char **argv){
    initialize_mock_arduino();

    myTimer.begin(blinkLED, 250000);
    delay(1000000);
}
```

## CMakelists.txt reference
* using macro from [cmake-declare-and-fetch](https://github.com/newdigate/cmake-declare-and-fetch)
  
``` cmake
project(thing C CXX)
include(cmake_declare_and_fetch.cmake.in)
DeclareAndFetch(teensy_x86_stubs https://github.com/newdigate/teensy-x86-stubs.git main src)
add_executable(thing main.cpp)
target_link_libraries(thing teensy_x86_stubs)
```

## build instructions:
``` sh
git clone https://github.com/newdigate/teensy-x86-stubs.git
cd teensy-x86-stubs
mkdir cmake-build-debug
cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```

## credits
* simial to [maniacbug/ncore](https://github.com/maniacbug/ncore)
* Don't Run Unit Tests on the Arduino Device or Emulator 
  * [stackoverflow 11437456](https://stackoverflow.com/a/11437456)
  * includes code from [IronSavior/dsm2_tx](https://github.com/IronSavior/dsm2_tx)
* cmake uninstaller 
  * [gist.github.com/royvandam/3033428](https://gist.github.com/royvandam/3033428)

## license
Unless specified in source code file, all code is MIT license.
