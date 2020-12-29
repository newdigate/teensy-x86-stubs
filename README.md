# teensy-x86-stubs
stub classes to allow basic teensy code and libraries to be compiled and debugged on your desktop PC.

## Don't Run Unit Tests on the Arduino Device or Emulator 
* https://stackoverflow.com/a/11437456
* includes code from https://github.com/IronSavior/dsm2_tx

## License
Unless specified in source code file, all code is MIT license.

## Quick example
* initialize_mock_arduino() will initialize the arduino timing library so that millis() will return the duration in milliseconds since the test app has been runnning. 
* To test teensy code accessing an SD card file, we call 
``` c++ 
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

##### CMakelists.txt
``` cmake
project(thing C CXX)

find_package(teensy_x86_stubs)

add_executable(thing
        main.cpp)

target_link_libraries(thing ${teensy_x86_stubs_LIBRARIES})

if (APPLE)
    # macOS: /usr/local/lib not a system library directory under CMake
    # https://gitlab.kitware.com/cmake/cmake/-/issues/19134
    target_link_libraries(thing -L/usr/local/lib)
endif()
```


### install:
``` sh
git clone https://github.com/newdigate/teensy-x86-stubs.git
cd teensy-x86-stubs
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
sudo make install
```

### uninstall:
``` sh
sudo make uninstall
```

