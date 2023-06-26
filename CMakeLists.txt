cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

# Project
project(metabolite_inference LANGUAGES CXX)

# Needed for Language Server Protocol
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Download coretools and stattools
include(FetchContent)
FetchContent_Declare(coretools
        GIT_REPOSITORY    https://bitbucket.org/wegmannlab/coretools.git
        GIT_TAG           master
        SOURCE_DIR        "${CMAKE_SOURCE_DIR}/coretools"
        )

FetchContent_Declare(stattools
        GIT_REPOSITORY    https://bitbucket.org/wegmannlab/stattools.git
        GIT_TAG           master
        SOURCE_DIR        "${CMAKE_SOURCE_DIR}/stattools"
        )

FetchContent_Declare(genometools
        GIT_REPOSITORY    https://bitbucket.org/wegmannlab/genometools.git
        GIT_TAG           master
        SOURCE_DIR        "${CMAKE_SOURCE_DIR}/genometools"
        )
FetchContent_MakeAvailable(coretools stattools genometools)

#######################
# Create core library
#######################
# assemble list of cpp and h files in core folder
file(GLOB_RECURSE CORE_SOURCES core/*.h core/*.cpp)

#Core library
add_library(coreLib STATIC ${CORE_SOURCES} core/TTree.h core/TTree.cpp)

target_sources(coreLib PRIVATE ${CORE_SOURCES})
target_include_directories(coreLib PRIVATE core SYSTEM INTERFACE core)
target_link_libraries(coreLib PUBLIC coretools stattools genometools)
target_compile_features(coreLib PUBLIC cxx_std_17)
set_target_properties(coreLib PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options(coreLib PRIVATE -Wall -Wextra)

#######################
# Executable
#######################

# add executable to be built
add_executable(${PROJECT_NAME}
        main.cpp
        core/TTree.cpp core/TTree.cpp core/TTree.h)

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
        coreLib
        )
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

#######################
# Tests
#######################
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        main
)
FetchContent_MakeAvailable(googletest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)

# define executable
add_executable("${PROJECT_NAME}_unitTests" EXCLUDE_FROM_ALL)

#assemble list of test cpp and h files
file(GLOB_RECURSE TEST_SOURCES tests/*.h tests/*.cpp)

target_include_directories("${PROJECT_NAME}_unitTests" PRIVATE coretools/core/IntegrationTests coretools/tests tests)

target_sources("${PROJECT_NAME}_unitTests" PRIVATE ${TEST_SOURCES})
target_link_libraries("${PROJECT_NAME}_unitTests" PRIVATE coreLib gtest_main gmock_main)
target_compile_features("${PROJECT_NAME}_unitTests" PRIVATE cxx_std_17)
target_compile_definitions("${PROJECT_NAME}_unitTests" PRIVATE CHECK_INTERVALS)
set_target_properties("${PROJECT_NAME}_unitTests" PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options("${PROJECT_NAME}_unitTests" PRIVATE -Wall -Wextra)

