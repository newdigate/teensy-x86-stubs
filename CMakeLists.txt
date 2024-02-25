cmake_minimum_required(VERSION 3.5)
project(teensy_x86_stubs C CXX)
set(teensy_x86_stubs_VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

option(BUILD_SHARED_LIBRARY "BUILD_SHARED_LIBRARY" OFF)
option(REDIRECT_SERIAL_OUT_TO_STD_OUT "REDIRECT_SERIAL_OUT_TO_STD_OUT" ON)

set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include/teensy_x86_stubs/")
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib/teensy_x86_stubs" )

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

IF (REDIRECT_SERIAL_OUT_TO_STD_OUT)
	add_compile_definitions(REDIRECT_SERIAL_OUT_TO_STD_OUT)
ENDIF ()

IF (BUILD_SHARED_LIBRARY)
	add_compile_definitions(BUILD_SHARED_LIBRARY)
ENDIF()

IF (NOT DEFINED BUILD_SHARED_LIBRARY)
	add_library(teensy_x86_stubs SHARED STATIC ${HEADER_FILES} ${SOURCE_FILES})
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
			"${CMAKE_COMMAND}" -P "../cmake/uninstall.cmake"
			)
ELSE ()
	add_library(teensy_x86_stubs SHARED ${HEADER_FILES} ${SOURCE_FILES})
ENDIF ()