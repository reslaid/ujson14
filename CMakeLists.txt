cmake_minimum_required(VERSION 3.0)

project(ujson14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(includes)

set(SOURCE_FILES
    examples/array.cpp
    includes/ujson/json.cpp
)

add_executable(ujson14.out ${SOURCE_FILES})

set(CMAKE_CXX_STANDARD 11)
add_executable(ujson11.out ${SOURCE_FILES})

set(CMAKE_CXX_STANDARD 17)
add_executable(ujson17.out ${SOURCE_FILES})

set(CMAKE_CXX_STANDARD 20)
add_executable(ujson20.out ${SOURCE_FILES})

set(CMAKE_CXX_STANDARD 23)
add_executable(ujson23.out ${SOURCE_FILES})