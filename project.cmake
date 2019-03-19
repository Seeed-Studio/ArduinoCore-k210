FILE(GLOB_RECURSE PROJ_LIB_SRC_INO
    "${CMAKE_CURRENT_LIST_DIR}/*.ino"
    )
SET_PROPERTY(SOURCE ${PROJ_LIB_SRC_INO} PROPERTY LANGUAGE CXX)
SET_SOURCE_FILES_PROPERTIES(${PROJ_LIB_SRC_INO} PROPERTIES COMPILE_FLAGS "-x c++")

include_directories(${CMAKE_CURRENT_LIST_DIR}/variants/k210
                    ${CMAKE_CURRENT_LIST_DIR}/cores/k210
                    ${SDK_ROOT}/third_party
                    ${SDK_ROOT}/lib/hal/include)
            
target_sources(${PROJECT_NAME} PUBLIC ${PROJ_LIB_SRC_INO})

