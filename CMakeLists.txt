cmake_minimum_required(VERSION 3.0.0)
project(Tetris VERSION 0.1.0)

# include(CTest)
# enable_testing()

add_executable(Tetris src/main.cpp)

target_link_libraries(Tetris SDL2 SDL_image SDL2_ttf)

set_target_properties(Tetris PROPERTIES OUTPUT_NAME "Tetris")

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
