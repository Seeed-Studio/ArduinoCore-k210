cmake_minimum_required(VERSION 3.0)

# basic config
if (NOT PROJ_PATH)
    message(FATAL_ERROR "PROJ_PATH must be set. e.g. -DPROJ_PATH=libraries/built-in/01.Basics/BareMinimum")
else()
    message("PROJ_PATH = ${PROJ_PATH}")
endif ()

# basic config
if (NOT BOARD)
    message(FATAL_ERROR "BOARD must be set. e.g. -BOARD=Grove AI Edge")
else()
    message("BOARD = ${BOARD}")
endif ()

## Use SDK builder to build this project
#include("tools/sdk/cmake/executable.cmake")
include(tools/sdk/cmake/common.cmake)

project(${PROJ})

set(ARDUINO_IDE "yes" CACHE INTERNAL "")

# set this will supress some warnings
set(BUILDING_SDK "yes" CACHE INTERNAL "")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


FILE(GLOB_RECURSE PROJ_LIB_SRC_INO
    "${PROJ_PATH}/*.ino"
    )

FILE(GLOB_RECURSE PROJ_LIB_SRC_C
        "${PROJ_PATH}/*.cpp"
        "${PROJ_PATH}/*.c"
        )

FILE(GLOB_RECURSE PROJ_ASSEMBLY_FILES
        "${PROJ_PATH}/*.s"
        "${PROJ_PATH}/*.S"
        )
SET(PROJ_SRC ${PROJ_LIB_SRC_INO} ${PROJ_LIB_SRC_C} ${PROJ_ASSEMBLY_FILES})

INCLUDE_DIRECTORIES(${PROJ_PATH})

#set_source_files_properties(${PROJ_LIB_SRC_INO} PROPERTIES LANGUAGE CXX)
SET_PROPERTY(SOURCE ${PROJ_LIB_SRC_INO} PROPERTY LANGUAGE CXX)
SET_SOURCE_FILES_PROPERTIES(${PROJ_LIB_SRC_INO} PROPERTIES COMPILE_FLAGS "-x c++")


SET_PROPERTY(SOURCE ${PROJ_ASSEMBLY_FILES} PROPERTY LANGUAGE C)
SET_SOURCE_FILES_PROPERTIES(${PROJ_ASSEMBLY_FILES} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp -D __riscv64")


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR}/tools/sdk/lib/arch/include 
                    ${CMAKE_CURRENT_LIST_DIR}/tools/sdk/lib/utils/include
                    ${CMAKE_CURRENT_LIST_DIR}/variants/${BOARD}
                    )


## Use SDK library API to add source files
add_source_files(${PROJ_SRC})
set(arduino_libs arduino_core)
include(tools/sdk/cmake/executable.cmake)
# other cmake instructions


add_subdirectory(tools/sdk)
add_subdirectory(cores/k210)
