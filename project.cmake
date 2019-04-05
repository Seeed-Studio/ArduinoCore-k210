if (MICROPYTHON)
include(${CMAKE_CURRENT_LIST_DIR}/micropython.cmake)
endif()

FILE(GLOB_RECURSE PROJ_LIB_SRC_INO
    "${CMAKE_CURRENT_LIST_DIR}/libraries/built-in/*.ino"
    )
SET_PROPERTY(SOURCE ${PROJ_LIB_SRC_INO} PROPERTY LANGUAGE CXX)
SET_SOURCE_FILES_PROPERTIES(${PROJ_LIB_SRC_INO} PROPERTIES COMPILE_FLAGS "-x c++")

add_definitions(-DARDUINO=1000 )

include_directories(${CMAKE_CURRENT_LIST_DIR}/variants/k210
                    ${CMAKE_CURRENT_LIST_DIR}/cores/k210
                    ${CMAKE_CURRENT_LIST_DIR}/libraries/Wire
                    ${CMAKE_CURRENT_LIST_DIR}/libraries/Accelerometer_ADXL345
                    ${CMAKE_CURRENT_LIST_DIR}/libraries/ADS1115
                    ${CMAKE_CURRENT_LIST_DIR}/libraries/micropython
                    ${SDK_ROOT}/third_party
                    ${SDK_ROOT}/lib/hal/include)
            
if (MICROPYTHON)
target_sources(${PROJECT_NAME} PUBLIC ${PROJ_LIB_SRC_INO} ${MICROPYTHON_SRC}  ${GENHDR}/qstrdefs.generated.h) 
else()
target_sources(${PROJECT_NAME} PUBLIC ${PROJ_LIB_SRC_INO})
endif()

if (LIBARDUINO)
FILE(GLOB_RECURSE LIBARDUINO_SRC
        "${CMAKE_CURRENT_LIST_DIR}/*.h"
        "${CMAKE_CURRENT_LIST_DIR}/*.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/*.c"
        "${CMAKE_CURRENT_LIST_DIR}/*.s"
        "${CMAKE_CURRENT_LIST_DIR}/*.S"
        )

FILE(GLOB_RECURSE LIBARDUINO_ASSEMBLY_FILES
        "${CMAKE_CURRENT_LIST_DIR}/*.s"
        "${CMAKE_CURRENT_LIST_DIR}/*.S"
        )

include_directories(${CMAKE_CURRENT_LIST_DIR}/cores/k210
                    ${CMAKE_CURRENT_LIST_DIR}/variants/k210)

SET_PROPERTY(SOURCE ${LIBARDUINO_ASSEMBLY_FILES} PROPERTY LANGUAGE C)
SET_SOURCE_FILES_PROPERTIES(${LIBARDUINO_ASSEMBLY_FILES} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp -D __riscv64")
#target_compile_definitions(arduino PRIVATE -DMICROPYTHON=${MICROPYTHON} )

ADD_LIBRARY(arduino
        ${LIBARDUINO_SRC}
        )
SET_TARGET_PROPERTIES(arduino PROPERTIES LINKER_LANGUAGE C)
set_target_properties(arduino PROPERTIES COMPILE_DEFINITIONS MICROPYTHON=${MICROPYTHON} )

endif ()