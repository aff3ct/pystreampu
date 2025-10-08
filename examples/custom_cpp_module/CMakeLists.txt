cmake_minimum_required(VERSION 3.6)
cmake_policy(SET CMP0054 NEW)
project (my_module)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Link with the "Threads library (required to link with AFF3CT after)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(PYBIND11_NEWPYTHON ON)

find_package(pybind11 CONFIG REQUIRED )

find_package(Threads REQUIRED)
find_package(cpptrace REQUIRED)
find_package(streampu REQUIRED)
#find_package(pystreampu REQUIRED)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pybind11/)
pybind11_add_module(my_module-lib MODULE ${SOURCES})

set_target_properties(my_module-lib PROPERTIES
                      OUTPUT_NAME my_module
                      POSITION_INDEPENDENT_CODE ON) # set -fpic

target_link_libraries     (my_module-lib PRIVATE spu::spu-static-lib)
target_include_directories(my_module-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
#target_include_directories(my_module-lib PUBLIC /Users/rtajan/Codes/sandbox/pystreampu/include)
