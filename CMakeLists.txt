cmake_minimum_required(VERSION 3.6)
cmake_policy(SET CMP0054 NEW)

project (${SKBUILD_PROJECT_NAME} LANGUAGES CXX)

#set(CMAKE_INSTALL_LIBDIR streampu)
#set(CMAKE_INSTALL_INCLUDEDIR streampu)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Link with the "Threads library (required to link with streampu after)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*)

# streampu
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/streampu/include/streampu.hpp")
    option(SPU_COMPILE_STATIC_LIB "" ON)
    option(SPU_COMPILE_SHARED_LIB "" OFF)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/streampu/)

    message(STATUS "Sub-project found: streampu")
else()
    message(FATAL_ERROR "streampu can't be found, try to init the submodule with the following cmd:\n"
                        "$ git submodule update --init --recursive")
endif()


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/pybind11/)
set(PYBIND11_NEWPYTHON ON)
# `pybind11_add_module` is a wrapper of the CMake `add_library` function
pybind11_add_module(_ext MODULE ${CMAKE_CURRENT_SOURCE_DIR}/src/ext.cpp ${SRC_FILES} ${HEADER_FILES})

set(pybind11_INCLUDE_DIRS)
install(TARGETS _ext DESTINATION .)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib/pybind11/include
        DESTINATION .
        FILES_MATCHING PATTERN "*.h")

include_directories(_ext PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(_ext PROPERTIES OUTPUT_NAME _ext
                           POSITION_INDEPENDENT_CODE ON
                           PRIVATE VERSION_INFO=${VERSION_INFO}) #  set -fpic

target_link_libraries(_ext PRIVATE spu-static-lib)

message("############################################################")
message("# CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}")
message("# CMAKE_CXX_FLAGS : ${CMAKE_CXX_FLAGS}")
message("# SKBUILD_PROJECT_NAME : ${SKBUILD_PROJECT_NAME}")
message("############################################################")