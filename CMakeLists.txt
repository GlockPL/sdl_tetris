cmake_minimum_required(VERSION 3.0.0)
project(Tetris VERSION 1.1.1)

# Platform-specific settings
if(WIN32)
    # Windows-specific SDL2 setup
    if(DEFINED ENV{SDL2_DIR})
        set(SDL2_DIR $ENV{SDL2_DIR})
    endif()
    if(DEFINED ENV{SDL2_TTF_DIR})
        set(SDL2_TTF_DIR $ENV{SDL2_TTF_DIR})
    endif()

    # Set include and library paths directly (structure matches Linux after restructuring in CI)
    set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
    set(SDL2_TTF_INCLUDE_DIR "${SDL2_TTF_DIR}/include")

    set(SDL2_LIBRARY "${SDL2_DIR}/lib/x64/SDL2.lib")
    set(SDL2MAIN_LIBRARY "${SDL2_DIR}/lib/x64/SDL2main.lib")
    set(SDL2_TTF_LIBRARY "${SDL2_TTF_DIR}/lib/x64/SDL2_ttf.lib")

    message(STATUS "SDL2 Include: ${SDL2_INCLUDE_DIR}")
    message(STATUS "SDL2 Library: ${SDL2_LIBRARY}")
    message(STATUS "SDL2_ttf Include: ${SDL2_TTF_INCLUDE_DIR}")
    message(STATUS "SDL2_ttf Library: ${SDL2_TTF_LIBRARY}")

    # Include both the base directory and SDL2 subdirectory
    # This allows both #include <SDL2/SDL.h> and #include <SDL.h> (used internally by SDL_ttf.h)
    set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR} ${SDL2_INCLUDE_DIR}/SDL2 ${SDL2_TTF_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR}/SDL2)
    set(SDL2_LIBRARIES ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY})
    set(SDL2_TTF_LIBRARIES ${SDL2_TTF_LIBRARY})
else()
    # Linux/Unix SDL2 setup
    find_package(SDL2 REQUIRED)

    # Try pkg-config for SDL2_ttf
    find_package(PkgConfig)
    if(PkgConfig_FOUND)
        pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
    else()
        # Fallback if pkg-config not available
        find_library(SDL2_TTF_LIBRARIES SDL2_ttf REQUIRED)
    endif()
endif()

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(src/)
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.hpp)

add_executable(Tetris src/main.cpp)

target_link_libraries(Tetris ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

set_target_properties(Tetris PROPERTIES OUTPUT_NAME "Tetris")
target_compile_features(Tetris PRIVATE cxx_std_17)

# Only add sanitizer on non-Windows platforms
if(NOT WIN32)
    add_compile_options(-fsanitize=undefined)
endif()
