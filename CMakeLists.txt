# Project
project(empty)

cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 14)

# add libraries
add_subdirectory(commonutilities)

# locate external libraries
find_package(ZLIB REQUIRED)

set(LINK_LIBRARIES     
    coreLib
    commonutilities 
    ${ZLIB_LIBRARIES}
)

include_directories(
    core    
    commonutilities
)

#######################
# Create core library
#######################
# assemble list of cpp and h files in core folder
file(GLOB_RECURSE CORE_SOURCES core/*.h core/*.cpp)

#Core library
add_library(coreLib STATIC ${CORE_SOURCES})

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

# compile commands: by default, compile in Release mode
# type 'cmake -DCMAKE_BUILD_TYPE=Debug ..' in terminal for compiling in Debug mode
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

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
    commonutilities/tests
    tests
)
