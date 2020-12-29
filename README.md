# teensy-x86-stubs
stub classes to allow certain teensy code to be compiled and run on a desktop PC

## Don't Run Unit Tests on the Arduino Device or Emulator https://stackoverflow.com/a/11437456
includes code from https://github.com/IronSavior/dsm2_tx

# License
Unless specified in source code file, all code is MIT license.

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

### usage:

##### CMakelists.txt
``` cmake
project(thing C CXX)

find_package(teensy_x86_stubs)

add_executable(thing
        main.cpp)

target_link_libraries(thing ${teensy_x86_stubs_LIBRARIES})

if (APPLE)
    # macOS: /usr/local/lib not a system library directory under CMake: https://gitlab.kitware.com/cmake/cmake/-/issues/19134
    target_link_libraries(thing -L/usr/local/lib)
endif()
```
