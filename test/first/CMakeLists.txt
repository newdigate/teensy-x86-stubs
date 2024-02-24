cmake_minimum_required(VERSION 3.10)
project(basic_test C CXX)
set(CMAKE_CXX_STANDARD 17)

        ../../src/Arduino.h
        ../../src/Arduino.cpp
        ../../src/hardware_serial.h
        ../../src/hardware_serial.cpp
        ../../src/core_pins.h
        ../../src/core_pins.cpp
        ../../src/Stream.cpp
        ../../src/Stream.h
        ../../src/WString.cpp
        ../../src/WString.h
        ../../src/Print.cpp
        ../../src/Print.h
        ../../src/Printable.h
        ../../src/pins_arduino.h
        first.cpp
        )

set(CMAKE_VERBOSE_MAKEFILE 1)
