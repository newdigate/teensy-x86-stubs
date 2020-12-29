cmake_minimum_required(VERSION 3.5)

project(teensy_x86_stubs C CXX)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
		hardware_serial.cpp
        Arduino.cpp
		Print.cpp
		File.cpp
		SD.cpp
		utility/Sd2Card.cpp
		utility/SdFile.cpp
		utility/SdVolume.cpp)

set(HEADER_FILES
		hardware_serial.h
		Arduino.h
		Print.h
		Printable.h
		SD.h)

set(UTILITY_HEADER_FILES
		utility/Sd2Card.h
		utility/Sd2PinMap.h
		utility/SdFat.h
		utility/SdFatUtil.h
		utility/FatStructs.h
		utility/SdFatmainpage.h
		utility/SdInfo.h)

add_library(teensy_x86_stubs SHARED STATIC ${HEADER_FILES} ${UTILITY_HEADER_FILES} ${SOURCE_FILES})

set_target_properties(teensy_x86_stubs PROPERTIES PUBLIC_HEADER "hardware_serial.h;Arduino.h;Print.h;Printable.h;SD.h")

install(TARGETS teensy_x86_stubs DESTINATION
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
		PUBLIC_HEADER DESTINATION "include/teensy_x86_stubs"
		)

install(FILES
		${UTILITY_HEADER_FILES}
		DESTINATION "include/teensy_x86_stubs/utility" )

install(FILES
		${CMAKE_CURRENT_SOURCE_DIR}/cmake/teensy_x86_stubsConfig.cmake
		${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake
		DESTINATION "lib/cmake/teensy_x86_stubs" )

##
# copied from: https://gist.github.com/royvandam/3033428
# Add uninstall target
# Requirements: Copy the uninstall.cmake file to the appropriate CMAKE_MODULE_PATH.
#

add_custom_target(uninstall
		"${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake"
		)