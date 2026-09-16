cmake_minimum_required(VERSION 3.16)
project(The_Answer_Protocol VERSION 1.0 LANGUAGES CXX)

# Version
set(CMAKE_CXX_STANDARD 17)
# Norm
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Binaries on root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
# Export commands for VSCODE
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Variables
	# Headers
set(PRECOMPILED_HEADERS
    includes/common.hpp
)
	# Libraries
set(LIBRARIES
	Threads::Threads
	nlohmann_json::nlohmann_json
)

# Disables examples/tests from dependencies
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(JSON_BuildTests OFF CACHE BOOL "" FORCE)

# Dependencies
find_package(Threads REQUIRED)
add_subdirectory(libraries/raylib)
add_subdirectory(libraries/yaml-cpp)
add_subdirectory(libraries/json)

# Configuration
add_library(project_flags INTERFACE)
target_compile_options(project_flags INTERFACE -g -Wall -Wextra -Werror)
target_include_directories(project_flags INTERFACE includes)
target_link_libraries(project_flags INTERFACE  ${LIBRARIES})
target_precompile_headers(project_flags INTERFACE ${PRECOMPILED_HEADERS})

# Executable
add_executable(tap_server src/main.cpp)
add_executable(tap_cli_client src/cli/cli_main.cpp)
add_executable(tap_gui_client src/gui/gui_main.cpp)

# Add configurations
target_link_libraries(tap_server PRIVATE project_flags yaml-cpp)
target_link_libraries(tap_cli_client PRIVATE project_flags)
target_link_libraries(tap_gui_client PRIVATE project_flags raylib)
