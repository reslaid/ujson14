cmake_minimum_required(VERSION 3.0)

project(ujson14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(includes)

set(TESTING_EXAMPLE_SOURCE_FILES
    tests/unit.cpp
    includes/ujson/json.cpp
)

add_executable(ujson-test-std14.out ${TESTING_EXAMPLE_SOURCE_FILES})
