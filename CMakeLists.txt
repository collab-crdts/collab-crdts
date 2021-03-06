cmake_minimum_required(VERSION 3.14)
project(collabserver-datatypes)
message(STATUS "Building project ${PROJECT_NAME}")

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()


# Compiler flags
message(STATUS "Detected Operating System: ${CMAKE_SYSTEM_NAME}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    message(WARNING "No CMAKE_BUILD_TYPE set for ${PROJECT_NAME}: uses default Release")
    message(STATUS "Available build types: Debug Release RelWithDebInfo MinSizeRel")
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "CMAKE_BUILD_TYPE for ${PROJECT_NAME}: ${CMAKE_BUILD_TYPE}")


# Add lib headers
include_directories("${PROJECT_SOURCE_DIR}/include/")


# Examples
option(COLLABSERVER_DATATYPES_EXAMPLES "Build examples" OFF)
if(COLLABSERVER_DATATYPES_EXAMPLES)
    message(STATUS "Building examples for ${PROJECT_NAME}")
    add_executable(${PROJECT_NAME}-examplesCmRDT "${PROJECT_SOURCE_DIR}/examples/CmRDT/runAllExamples.cpp")
    add_custom_target(runExamplesCmRDT ${PROJECT_NAME}-examplesCmRDT)
endif()


# Tests
option(COLLABSERVER_DATATYPES_TESTS "Build tests" OFF)
if(COLLABSERVER_DATATYPES_TESTS)
    message(STATUS "Building tests for ${PROJECT_NAME}")
    enable_testing()

    # Tests executable
    file(GLOB_RECURSE srcFilesTests "${PROJECT_SOURCE_DIR}/tests/*.cpp")
    add_executable(${PROJECT_NAME}-tests ${srcFilesTests})

    # Googletest dependency
    add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest")
    include_directories("${PROJECT_SOURCE_DIR}/extern/googletest/googletest/include/")
    target_link_libraries(${PROJECT_NAME}-tests gtest)

    # Tests target
    add_test(NAME googletests COMMAND ${PROJECT_NAME}-tests)
    add_custom_target(runTests ${PROJECT_NAME}-tests)
endif()

