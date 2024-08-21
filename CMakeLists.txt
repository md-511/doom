cmake_minimum_required(VERSION 3.10)
project(Raycaster)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} include)

set(SOURCES
    src/main.cpp
    src/raycaster.cpp
)

add_executable(raycaster ${SOURCES})
target_link_libraries(raycaster ${SDL2_LIBRARIES})

set_target_properties(raycaster PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
