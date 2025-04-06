cmake_minimum_required(VERSION 3.5)
project(teensy_x86_stubs C CXX)
set(teensy_x86_stubs_VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
option(BUILD_DYNAMIC_LIBRARY Off)
add_compile_definitions(__IMXRT1062__)
add_compile_definitions(ARDUINO_TEENSY41)
add_compile_definitions(ARDUINO=158)
set(SOURCE_FILES
		hardware_serial.cpp
		Arduino.cpp
		Print.cpp
		Stream.cpp
		WString.cpp
        core_pins.cpp
		IntervalTimer.cpp
		AudioStream.cpp
		EventResponder.cpp
		digital.cpp
		arm_math.cpp)

if (MSVC)
	set(SOURCE_FILES ${SOURCE_FILES} src/ctz_clz.cpp)
endif()

set(HEADER_FILES
		hardware_serial.h
		Arduino.h
		Print.h
		Printable.h
		pins_arduino.h
		Stream.h
		WString.h
		nonstd.h
		AudioStream.h
        core_pins.h
		IntervalTimer.h
		EventResponder.h
		teensy_main.h
		imxrt.h
		arm_math.h
		elapsedMillis.h)

if (BUILD_DYNAMIC_LIBRARY)
	add_library(teensy_x86_stubs SHARED ${HEADER_FILES} ${SOURCE_FILES})
else ()
	add_library(teensy_x86_stubs SHARED STATIC ${HEADER_FILES} ${SOURCE_FILES})
endif ()