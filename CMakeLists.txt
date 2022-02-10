cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

# Project
project(empty LANGUAGES CXX)

# Needed for Language Server Protocol
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Download coretools and stattools
include(FetchContent)
FetchContent_Declare(coretools
        GIT_REPOSITORY    https://bitbucket.org/wegmannlab/coretools.git
        GIT_TAG           master
        SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/coretools"
        )
FetchContent_MakeAvailable(coretools)

#######################
# Create core library
#######################
# assemble list of cpp and h files in core folder
file(GLOB_RECURSE CORE_SOURCES core/*.h core/*.cpp)

#Core library
add_library(coreLib STATIC ${CORE_SOURCES})

target_sources(coreLib PRIVATE ${CORE_SOURCES})
target_include_directories(coreLib PRIVATE core SYSTEM INTERFACE core)
target_link_libraries(coreLib PUBLIC coretools)
target_compile_features(coreLib PUBLIC cxx_std_17)
set_target_properties(coreLib PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options(coreLib PRIVATE -Wall -Wextra)

#######################
# Executable
#######################

# add executable to be built
add_executable(${PROJECT_NAME}
        main.cpp
        )

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
        coreLib
        )
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

#######################
# Tests
#######################
#assemble list of test cpp and h files
file(GLOB_RECURSE TEST_SOURCES tests/*.h tests/*.cpp)

add_executable("${PROJECT_NAME}_unitTests" EXCLUDE_FROM_ALL ${TEST_SOURCES})

target_link_libraries("${PROJECT_NAME}_unitTests" PUBLIC
        gtest_main
        gmock_main
        coreLib
        )

target_include_directories("${PROJECT_NAME}_unitTests" PUBLIC
        "${PROJECT_BINARY_DIR}" #google tests will be cloned in there
        coretools/tests
        tests
        )
