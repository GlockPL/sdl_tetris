cmake_minimum_required(VERSION 3.0.0)
project(Tetris VERSION 0.1.0)

# include(CTest)
# enable_testing()


find_package(SDL2 REQUIRED)
# find_package(SDL2_TTF REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
file(GLOB src/ CONFIGURE_DEPENDS "*.hpp")

add_executable(Tetris src/main.cpp)

target_link_libraries(Tetris SDL2 SDL2_ttf)

set_target_properties(Tetris PROPERTIES OUTPUT_NAME "Tetris")
target_compile_features(Tetris PRIVATE cxx_std_17)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
