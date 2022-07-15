cmake_minimum_required(VERSION 3.0.0)
project(Tetris VERSION 0.1.0)

find_package(SDL2 REQUIRED)
# find_package(SDL2_TTF REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(src/)
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.hpp )

add_executable(Tetris src/main.cpp)

target_link_libraries(Tetris SDL2 SDL2_ttf)

set_target_properties(Tetris PROPERTIES OUTPUT_NAME "Tetris")
target_compile_features(Tetris PRIVATE cxx_std_17)
add_compile_options(-fsanitize=undefined)
