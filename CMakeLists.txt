cmake_minimum_required(VERSION 3.5)
project(teensy_x86_stubs C CXX)
set(teensy_x86_stubs_VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include/teensy_x86_stubs/)
set(LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib/teensy_x86_stubs )

set(SOURCE_FILES
		src/hardware_serial.cpp
		src/Arduino.cpp
		src/Print.cpp
		src/File.cpp
		src/SD.cpp
		src/Stream.cpp
		src/WString.cpp
		src/utility/Sd2Card.cpp
		src/utility/SdFile.cpp
		src/utility/SdVolume.cpp)

set(HEADER_FILES
		src/hardware_serial.h
		src/Arduino.h
		src/Print.h
		src/Printable.h
		src/SD.h
		src/spi_interrupt.h
		src/pins_arduino.h
		src/Stream.h
		src/WString.h
		src/nonstd.h)

set(UTILITY_HEADER_FILES
		src/utility/Sd2Card.h
		src/utility/Sd2PinMap.h
		src/utility/SdFat.h
		src/utility/SdFatUtil.h
		src/utility/FatStructs.h
		src/utility/SdFatmainpage.h
		src/utility/SdInfo.h)

add_library(teensy_x86_stubs SHARED STATIC ${HEADER_FILES} ${UTILITY_HEADER_FILES} ${SOURCE_FILES})

set_target_properties(teensy_x86_stubs PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")

include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/teensy_x86_stubs.cmake.in
		${CMAKE_CURRENT_BINARY_DIR}/teensy_x86_stubsConfig.cmake
		INSTALL_DESTINATION ${LIB_INSTALL_DIR}/teensy_x86_stubs/cmake
		PATH_VARS)

write_basic_package_version_file(
		${CMAKE_CURRENT_BINARY_DIR}/teensy_x86_stubsConfigVersion.cmake
		VERSION ${teensy_x86_stubs_VERSION}
		COMPATIBILITY SameMajorVersion )

install(TARGETS teensy_x86_stubs DESTINATION
		LIBRARY DESTINATION ${LIB_INSTALL_DIR}
		ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
		PUBLIC_HEADER DESTINATION "include/teensy_x86_stubs"
		)

install(FILES
		${UTILITY_HEADER_FILES}
		DESTINATION "include/teensy_x86_stubs/utility" )

install(FILES
		${CMAKE_CURRENT_BINARY_DIR}/teensy_x86_stubsConfig.cmake
		${CMAKE_CURRENT_BINARY_DIR}/teensy_x86_stubsConfigVersion.cmake
		cmake/uninstall.cmake
		DESTINATION "lib/cmake/teensy_x86_stubs" )

##
# copied from: https://gist.github.com/royvandam/3033428
# Add uninstall target
# Requirements: Copy the uninstall.cmake file to the appropriate CMAKE_MODULE_PATH.
#

add_custom_target(uninstall
		"${CMAKE_COMMAND}" -P "cmake/uninstall.cmake"
		)