# Project
project(empty)

cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

# Maximal
#set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra  -Weffc++ -Wconversion -Wsign-conversion -Wpedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Woverloaded-virtual -Wlogical-op -Wdouble-promotion -Wformat=2")

# Reasonable
#set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -pedantic -Wno-long-long -Wno-strict-aliasing")

# Minimal
set(CMAKE_CXX_FLAGS "-Wall  -Wextra")

# Needed for Language Server Protocol
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# compile commands: by default, compile in Release mode
# type 'cmake -DCMAKE_BUILD_TYPE=Debug ..' in terminal for compiling in Debug mode
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# locate external libraries
find_package(ZLIB REQUIRED)
find_package(Armadillo REQUIRED)

# Download coretools and stattools
include(FetchContent)
FetchContent_Declare(coretools
        GIT_REPOSITORY    https://glis-glis@bitbucket.org/wegmannlab/coretools.git
        GIT_TAG           master
        SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/coretools"
        )
FetchContent_MakeAvailable(coretools)

# locate external libraries
find_package(ZLIB REQUIRED)

set(LINK_LIBRARIES
        coreLib
        coretools
        ${ZLIB_LIBRARIES}
        )

include_directories(
        core
        coretools/core
        coretools/core/Types
)

#######################
# Create core library
#######################
# assemble list of cpp and h files in core folder
file(GLOB_RECURSE CORE_SOURCES core/*.h core/*.cpp)

#Core library
add_library(coreLib STATIC ${CORE_SOURCES})
target_compile_definitions(coreLib PUBLIC)

#######################
# Executable
#######################

# add executable to be built
add_executable(${PROJECT_NAME}
        main.cpp
        )

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
        ${LINK_LIBRARIES}
        )

# add the binary tree to the search path for include files
target_include_directories(${PROJECT_NAME} PUBLIC)

#######################
# Tests
#######################
#assemble list of test cpp and h files
file(GLOB_RECURSE TEST_SOURCES tests/*.h tests/*.cpp)

add_executable("${PROJECT_NAME}_unitTests" EXCLUDE_FROM_ALL ${TEST_SOURCES})

target_link_libraries("${PROJECT_NAME}_unitTests" PUBLIC
        gtest_main
        gmock_main
        ${LINK_LIBRARIES}
        )

target_include_directories("${PROJECT_NAME}_unitTests" PUBLIC
        "${PROJECT_BINARY_DIR}" #google tests will be cloned in there
        coretools/tests
        tests
        )
