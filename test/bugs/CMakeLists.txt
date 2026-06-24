cmake_minimum_required(VERSION 3.10)
project(bugs_test C CXX)
set(CMAKE_CXX_STANDARD 17)

# Unlike the other test apps, this one builds against the LOCAL working copy of
# the library (../../src) so it verifies the code in this checkout rather than
# whatever is on GitHub main.
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../src)
file(GLOB LIB_SOURCES ${LIB_DIR}/*.cpp)
if (NOT MSVC)
    list(REMOVE_ITEM LIB_SOURCES ${LIB_DIR}/ctz_clz.cpp)  # MSVC-only intrinsics
endif()

add_compile_definitions(__IMXRT1062__ ARDUINO_TEENSY41 ARDUINO=158)
include_directories(${LIB_DIR})

add_executable(bugs bugs.cpp ${LIB_SOURCES})
find_package(Threads REQUIRED)
target_link_libraries(bugs Threads::Threads)
