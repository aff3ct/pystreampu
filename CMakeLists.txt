cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0054 NEW)

if (CMAKE_GENERATOR MATCHES "Ninja")
    file(
        WRITE "${CMAKE_BINARY_DIR}/GNUMakeRulesOverwrite.cmake"
            "STRING(REPLACE \"-MD\" \"-MMD\" CMAKE_DEPFILE_FLAGS_C \"\${CMAKE_DEPFILE_FLAGS_C}\")\n"
            "STRING(REPLACE \"-MD\" \"-MMD\" CMAKE_DEPFILE_FLAGS_CXX \"\${CMAKE_DEPFILE_FLAGS_CXX}\")\n"
    )
    set(CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_BINARY_DIR}/GNUMakeRulesOverwrite.cmake" CACHE INTERNAL "")
endif()

project (pystreampu LANGUAGES CXX)

option(INCLUDE_SPU_LIB "Include the StreamPU library inside the AFF3CT library" ON)

#set(CMAKE_INSTALL_LIBDIR streampu)
#set(CMAKE_INSTALL_INCLUDEDIR streampu)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Link with the "Threads library (required to link with streampu after)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
include(GNUInstallDirs)
#
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*)


#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/pybind11/)
set(PYBIND11_NEWPYTHON ON)
find_package(pybind11 CONFIG 3.0 REQUIRED)
# `pybind11_add_module` is a wrapper of the CMake `add_library` function
pybind11_add_module(_ext MODULE ${CMAKE_CURRENT_SOURCE_DIR}/src/ext.cpp ${SRC_FILES} ${HEADER_FILES})

# set(pybind11_INCLUDE_DIRS)
if (NOT INCLUDE_SPU_LIB)
        message(STATUS "Using user installed StreamPU library")
        find_package(cpptrace REQUIRED)
        if (NOT cpptrace_FOUND)
                message(FATAL_ERROR "cpptrace library not found")
        endif()
        message(STATUS "Found cpptrace: ${cpptrace_DIR}")
        target_link_libraries(_ext PUBLIC cpptrace::cpptrace)

        find_package(StreamPU CONFIG 1.8.1 REQUIRED)
        if (NOT StreamPU_FOUND)
                message(FATAL_ERROR "StreamPU library not found")
        endif()
        message(STATUS "Found StreamPU: ${StreamPU_DIR}")
        target_link_libraries(_ext PRIVATE spu::spu-static-lib)
else()
        # streampu
        message(STATUS "Including StreamPU sub-project")
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/streampu/include/streampu.hpp")
        option(SPU_COMPILE_STATIC_LIB "" ON)
        option(SPU_COMPILE_SHARED_LIB "" OFF)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/streampu/)

        message(STATUS "Sub-project found: streampu")
        else()
        message(FATAL_ERROR "streampu can't be found, try to init the submodule with the following cmd:\n"
                                "$ git submodule update --init --recursive")
        endif()

        target_link_libraries(_ext PRIVATE spu-static-lib)

endif()

set(pybind11_INCLUDE_DIRS)

include_directories(_ext PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(_ext PROPERTIES OUTPUT_NAME _ext
                           POSITION_INDEPENDENT_CODE ON
                           PRIVATE VERSION_INFO=${VERSION_INFO}) #  set -fpic


# Install pybind11 headers
# install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/pybind11/include/pybind11
#         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#         COMPONENT headers
#         FILES_MATCHING PATTERN "*.h")

install(TARGETS _ext
        DESTINATION .
        EXPORT pystreampu-config
        COMPONENT library)

install(EXPORT
        pystreampu-config
        DESTINATION "share/cmake/pystreampu"
        NAMESPACE pyspu::
        COMPONENT library)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pystreampu
        COMPONENT headers
        FILES_MATCHING PATTERN "*.hpp")

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pystreampu
        COMPONENT headers
        FILES_MATCHING PATTERN "*.hxx")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pystreampu
        COMPONENT headers
        FILES_MATCHING PATTERN "*.h")

message("############################################################")
message("# CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}")
message("# CMAKE_CXX_FLAGS : ${CMAKE_CXX_FLAGS}")
message("# SKBUILD_PROJECT_NAME : streampu")
message("############################################################")