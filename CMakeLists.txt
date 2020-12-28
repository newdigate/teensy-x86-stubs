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

target_include_directories(teensy_x86_stubs
		PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		)



##
# copied from: https://gist.github.com/royvandam/3033428
# Add uninstall target
# Requirements: Copy the uninstall.cmake file to the appropriate CMAKE_MODULE_PATH.
#

add_custom_target(uninstall
		"${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake"
		)

install(TARGETS teensy_x86_stubs
		EXPORT teensy_x86_stubs-export
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
		)
install(EXPORT teensy_x86_stubs-export
		FILE
		teensy_x86_stubsTargets.cmake
		NAMESPACE
		teensy_x86_stubs::
		DESTINATION
		lib/cmake/teensy_x86_stubs
		)
install(FILES
		${CMAKE_CURRENT_SOURCE_DIR}/Arduino.h
		${CMAKE_CURRENT_SOURCE_DIR}/hardware_serial.h
		${CMAKE_CURRENT_SOURCE_DIR}/Teensy/Print.h
		${CMAKE_CURRENT_SOURCE_DIR}/SD/SD.h
		DESTINATION "include/teensy_x86_stubs")
install(FILES
		${CMAKE_CURRENT_SOURCE_DIR}/cmake/teensy_x86_stubsConfig.cmake
		${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake
		DESTINATION "lib/cmake/teensy_x86_stubs" )