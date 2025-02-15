cmake_minimum_required(VERSION 3.5)
project(teensy_x86_stubs C CXX)
set(teensy_x86_stubs_VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(__IMXRT1062__)
add_compile_definitions(ARDUINO_TEENSY41)
add_compile_definitions(ARDUINO=158)
set(SOURCE_FILES
		src/hardware_serial.cpp
		src/Arduino.cpp
		src/Print.cpp
		src/Stream.cpp
		src/WString.cpp
        src/core_pins.cpp
		src/IntervalTimer.cpp
		src/AudioStream.cpp
		src/digital.cpp
		src/arm_math.cpp)

if (MSVC)
	set(SOURCE_FILES ${SOURCE_FILES} src/ctz_clz.cpp)
endif()

set(HEADER_FILES
		src/hardware_serial.h
		src/Arduino.h
		src/Print.h
		src/Printable.h
		src/pins_arduino.h
		src/Stream.h
		src/WString.h
		src/nonstd.h
		src/AudioStream.h
        src/core_pins.h
		src/IntervalTimer.h
		src/teensy_main.h
		src/imxrt.h
		src/arm_math.h
		src/elapsedMillis.h)

add_library(teensy_x86_stubs SHARED STATIC ${HEADER_FILES} ${SOURCE_FILES})
