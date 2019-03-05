cmake_minimum_required(VERSION 3.0)

set(ARDUINO_IDE "yes" CACHE INTERNAL "")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


add_subdirectory(tools/sdk)
