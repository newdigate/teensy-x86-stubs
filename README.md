# teensy x86 stubs
[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![blink](https://github.com/newdigate/teensy-x86-stubs/actions/workflows/blink.yml/badge.svg)](https://github.com/newdigate/teensy-x86-stubs/actions/workflows/blink.yml)
[![first](https://github.com/newdigate/teensy-x86-stubs/actions/workflows/first.yml/badge.svg)](https://github.com/newdigate/teensy-x86-stubs/actions/workflows/first.yml)
[![root](https://github.com/newdigate/teensy-x86-stubs/actions/workflows/root.yml/badge.svg)](https://github.com/newdigate/teensy-x86-stubs/actions/workflows/root.yml)
[![bugs](https://github.com/newdigate/teensy-x86-stubs/actions/workflows/bugs.yml/badge.svg)](https://github.com/newdigate/teensy-x86-stubs/actions/workflows/bugs.yml)

stub classes implementing basic arduino/teensy functions for compiling and debugging on your x86/x64 architecture (Linux, macOS, Windows/MSVC)

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
### main.cpp
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
* the `DeclareAndFetch` macro comes from [cmake-declare-and-fetch](https://github.com/newdigate/cmake-declare-and-fetch) —
  copy its `cmake_declare_and_fetch.cmake.in` next to your `CMakeLists.txt` (see `test/` in this repo for an example)
  
``` cmake
cmake_minimum_required(VERSION 3.10)
project(thing C CXX)
set(CMAKE_CXX_STANDARD 17)
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
* this builds only the `teensy_x86_stubs` library. To actually run something, build one of the
  standalone test apps (e.g. `test/blink` or `test/first`), each of which has its own `CMakeLists.txt`.

## timing emulation
* to initialize the arduino timing library so that millis() will return the duration in milliseconds since the test app has been running
``` c++
    initialize_mock_arduino()
```

## credits
* similar to [maniacbug/ncore](https://github.com/maniacbug/ncore)
* Don't Run Unit Tests on the Arduino Device or Emulator 
  * [stackoverflow 11437456](https://stackoverflow.com/a/11437456)
  * includes code from [IronSavior/dsm2_tx](https://github.com/IronSavior/dsm2_tx)
* cmake uninstaller 
  * [gist.github.com/royvandam/3033428](https://gist.github.com/royvandam/3033428)

## license
Unless specified in source code file, all code is MIT license.
