cmake_minimum_required(VERSION 3.0.0)
project(Tetris VERSION 1.1.0)

# Platform-specific settings
if(WIN32)
    # Windows-specific SDL2 setup
    if(DEFINED ENV{SDL2_DIR})
        set(SDL2_DIR $ENV{SDL2_DIR})
    endif()
    if(DEFINED ENV{SDL2_TTF_DIR})
        set(SDL2_TTF_DIR $ENV{SDL2_TTF_DIR})
    endif()

    # Find SDL2
    find_path(SDL2_INCLUDE_DIR SDL.h
        HINTS ${SDL2_DIR}
        PATH_SUFFIXES include
    )
    find_library(SDL2_LIBRARY SDL2
        HINTS ${SDL2_DIR}
        PATH_SUFFIXES lib/x64 lib
    )
    find_library(SDL2MAIN_LIBRARY SDL2main
        HINTS ${SDL2_DIR}
        PATH_SUFFIXES lib/x64 lib
    )

    # Find SDL2_ttf
    find_path(SDL2_TTF_INCLUDE_DIR SDL_ttf.h
        HINTS ${SDL2_TTF_DIR}
        PATH_SUFFIXES include
    )
    find_library(SDL2_TTF_LIBRARY SDL2_ttf
        HINTS ${SDL2_TTF_DIR}
        PATH_SUFFIXES lib/x64 lib
    )

    set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
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
