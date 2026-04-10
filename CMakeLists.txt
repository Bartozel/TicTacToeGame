# CMakeLists.txt
# -----------------------------------------------------------------------------
# Purpose: The build system definition for this project.
# CMake reads this file and generates native build files (Makefiles on macOS/Linux,
# .sln/.vcxproj on Windows). You never edit Makefiles directly — you edit this
# file and let CMake regenerate them.
#
# Typical workflow:
#   1. Edit CMakeLists.txt (add sources, change settings, add libraries)
#   2. Run: cmake .. -DCMAKE_BUILD_TYPE=Debug   (configure — generates Makefiles)
#   3. Run: cmake --build .                      (build — compiles the sources)
#
# If you only change source files (not CMakeLists.txt), step 2 is not needed.
# -----------------------------------------------------------------------------

# Minimum CMake version required to process this file.
# Version 3.20 introduced features used below. Older CMake installations
# will print an error instead of producing a broken build silently.
cmake_minimum_required(VERSION 3.20)

# Names the project. Sets the CMake variable ${PROJECT_NAME} = "TicTacToeGame".
# Also used as the default binary/library name.
project(TicTacToeGame)

# Set a default build type when none is specified on the command line.
# Without this, CMAKE_BUILD_TYPE is empty and the compiler uses no optimization
# or debug flags — breakpoints won't work and symbols are missing.
# Override at configure time with: cmake .. -DCMAKE_BUILD_TYPE=Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# C++ language standard.
# "20" enables C++20 features (concepts, ranges, std::format, etc.).
# CMAKE_CXX_STANDARD_REQUIRED=ON makes CMake error out if the compiler
# does not support C++20, instead of silently falling back to an older standard.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export the exact compiler command for every source file into build/compile_commands.json.
# VSCode's IntelliSense reads this file to use the same flags as the real build,
# eliminating false "symbol not found" errors caused by mismatched settings.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Collect source files.
# GLOB matches all .cpp files directly in the project root (non-recursive).
# GLOB_RECURSE descends into the listed subdirectories.
# Note: if you add or remove .cpp files you must re-run CMake configure so
# the file list is refreshed. The build system does not detect new files automatically.
file(GLOB SOURCES "*.cpp")
file(GLOB_RECURSE SOURCES_SUBDIRS "Board/*.cpp" "Data/*.cpp" "Game/*.cpp")
list(APPEND SOURCES ${SOURCES_SUBDIRS})

# Declare the executable target.
# CMake will compile every file in ${SOURCES} and link them into a single binary
# named "TicTacToeGame" (placed in the build directory).
add_executable(TicTacToeGame ${SOURCES})

# Add the project root to the compiler's include search path.
# This allows source files to use #include "SomeHeader.h" regardless of
# which subdirectory they live in, without needing relative paths like
# #include "../../SomeHeader.h".
target_include_directories(TicTacToeGame PRIVATE ${CMAKE_SOURCE_DIR})
