cmake_minimum_required(VERSION 3.10)
project(blink_test C CXX)
set(CMAKE_CXX_STANDARD 17)
include(../cmake_declare_and_fetch.cmake.in)
DeclareAndFetch(teensy_x86_stubs https://github.com/newdigate/teensy-x86-stubs.git main src)

add_executable(blink        blink.cpp)
target_link_libraries(blink teensy_x86_stubs)
