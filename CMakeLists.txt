cmake_minimum_required(VERSION 3.0)
project(MeowXMonster)
set(CMAKE_C_STANDARD 99)

# Check if we are compiling for ARM32 and Linux
if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "armv7l" AND ${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(EXTRA_LIBS "-latomic") # Link the libatomic library with -latomic flag
    target_compile_definitions(${PROJECT_NAME} PUBLIC MESA_GLSL_VERSION_OVERRIDE=330) # Set GLSL version to 330
    target_compile_definitions(${PROJECT_NAME} PUBLIC MESA_GL_VERSION_OVERRIDE=3.3) # Set GL version to 3.3
endif()

# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)
set(PROJECT_SOURCES
    App.c
    src/c/gameover.c
    src/c/startgame.c
    src/c/game.c
    src/c/character/character.c
    src/asm/cal.s
    src/asm/cal.o
)

# Adding our source files
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/") # Define PROJECT_INCLUDE to be the path to the include directory of the project

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib ${EXTRA_LIBS}) # Link with raylib and any extra libraries

# Setting ASSETS_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable
