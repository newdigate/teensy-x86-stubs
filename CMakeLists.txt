cmake_minimum_required(VERSION 3.5)

project(teensy_x86_stubs C CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(teensy_x86_stubs STATIC
		hardware_serial.cpp
        hardware_serial.h
        Arduino.cpp
		Arduino.h
        Teensy/Print.cpp
        Teensy/Print.h
        Teensy/Printable.h
        SD/File.cpp
        SD/SD.cpp
        SD/SD.h
        SD/utility/FatStructs.h
        SD/utility/Sd2Card.cpp
        SD/utility/Sd2Card.h
        SD/utility/Sd2PinMap.h
        SD/utility/SdFat.h
        SD/utility/SdFatUtil.h
        SD/utility/SdFatmainpage.h
        SD/utility/SdFile.cpp
        SD/utility/SdInfo.h
        SD/utility/SdVolume.cpp)
