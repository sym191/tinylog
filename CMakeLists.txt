cmake_minimum_required(VERSION 3.25)
project(tinylog LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(tinylog
    INTERFACE
)

target_include_directories(tinylog
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(main
    examples/main.cpp
)

target_link_libraries(main 
    PUBLIC
    tinylog
)
