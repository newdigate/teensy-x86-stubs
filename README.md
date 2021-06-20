# teensy x86 stubs
[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![CMake](https://img.shields.io/badge/project-CMake-brightgreen.svg?label=built%20with&colorA=555555&colorB=8a8fff&logo=)](CMakelists.txt)
[![CMake](https://github.com/newdigate/teensy-x86-stubs/workflows/CMake/badge.svg)](https://github.com/newdigate/teensy-x86-stubs/actions)

installable cmake package with stub classes to allow basic teensy code and libraries to be compiled and debugged on your x86/x64 architecture

* [quick example](#quick-example)
  * [main.cpp](#maincpp)
  * [output](#output)
  * [CMakelists.txt](#cmakeliststxt)
* [package installation](#package-installation)
* [uninstall](#uninstall)
* [credits](#credits)
* [license](#license)


## quick example
* to initialize the arduino timing library so that millis() will return the duration in milliseconds since the test app has been runnning
``` c++
    initialize_mock_arduino()
```
* To test teensy code accessing an SD card file, you'll need to install [teensy-x86-sd-stubs](https://github.com/newdigate/teensy-x86-sd-stubs)
``` c++ 
    char *buffer = "blah blah blah blah blah";
    SD.setSDCardFileData(buffer, strlen(buffer));
```

##### main.cpp
``` c++
#include <Arduino.h>
#include <SD.h>

using namespace std;

int main(int argc, char **argv){
    std::cout << "starting app...\n";
    initialize_mock_arduino();

    char *buffer = "blah blah blah blah blah";
    SD.setSDCardFileData(buffer, strlen(buffer));

    File f = SD.open("abcdefg.123");

    char *output = new char[1000];
    int bytesRead = f.read(output, 1000);

    std::cout << bytesRead << " bytes read: \n" << output;
}
```
##### output
```
starting app...
24 bytes read: 
blah blah blah blah blah
```

##### CMakelists.txt
``` cmake
project(thing C CXX)

find_package(teensy_x86_stubs)
include_directories(${teensy_x86_stubs_INCLUDE_DIR})

add_executable(thing main.cpp)

target_link_libraries(thing ${teensy_x86_stubs_LIBS})
```


## package installation:
``` sh
git clone https://github.com/newdigate/teensy-x86-stubs.git
cd teensy-x86-stubs
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
sudo make install
```

## uninstall:
``` sh
sudo make uninstall
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
