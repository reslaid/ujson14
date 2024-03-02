cmake_minimum_required(VERSION 3.0)

project(ujson14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(includes)

set(ARR_EXAMPLE_SOURCE_FILES
    examples/array.cpp
    includes/ujson/json.cpp
)

set(OBJECTS_EXAMPLE_SOURCE_FILES
    examples/objects.cpp
    includes/ujson/json.cpp
)

add_executable(ujson-array_example-std14.out ${ARR_EXAMPLE_SOURCE_FILES})
add_executable(ujson-objects_example-std14.out ${OBJECTS_EXAMPLE_SOURCE_FILES})
