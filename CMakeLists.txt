cmake_minimum_required(VERSION 3.6)
cmake_policy(SET CMP0054 NEW)

project (pyaf VERSION ${VERSION_INFO})

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
MESSAGE( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )

# Link with the "Threads library (required to link with AFF3CT after)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*)

# aff3ct-core
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/aff3ct-core/include/aff3ct-core.hpp")
    option(AFF3CT_CORE_COMPILE_STATIC_LIB "" ON)
    option(AFF3CT_CORE_COMPILE_SHARED_LIB "" OFF)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/aff3ct-core/)

    message(STATUS "Sub-project found: aff3ct-core")
else()
    message(FATAL_ERROR "aff3ct-core can't be found, try to init the submodule with the following cmd:\n"
                        "$ git submodule update --init --recursive")
endif()


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/pybind11/)

# `pybind11_add_module` is a wrapper of the CMake `add_library` function
pybind11_add_module(_ext MODULE ${CMAKE_CURRENT_SOURCE_DIR}/src/pyaf.cpp ${SRC_FILES} ${HEADER_FILES})

set(pybind11_INCLUDE_DIRS)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib/pybind11/include
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        FILES_MATCHING PATTERN "*.h")

include_directories(_ext PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(_ext PROPERTIES OUTPUT_NAME _ext
                           POSITION_INDEPENDENT_CODE ON
                           PRIVATE VERSION_INFO=${VERSION_INFO}) #  set -fpic

target_link_libraries(_ext PRIVATE aff3ct-core-static-lib)

