cmake_minimum_required(VERSION 3.10)

project(DoomStyleGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)

include_directories(${CMAKE_SOURCE_DIR}/include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

set(SOURCES
    src/main.cpp
    src/raycaster.cpp
)

add_executable(game ${SOURCES})

target_link_libraries(game ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

set_target_properties(game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
