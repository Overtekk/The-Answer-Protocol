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

#Disable examples and tests from submodules
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(JSON_BuildTests OFF CACHE BOOL "" FORCE)

# Dependencies
find_package(Threads REQUIRED)
add_subdirectory(libraries/raylib)
add_subdirectory(libraries/yaml-cpp)
add_subdirectory(libraries/json)

# Config
add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE -g -Wall -Wextra -Werror)
target_include_directories(project_warnings INTERFACE includes)

# -------------#
#   Variables
# -------------#

set(COMMON_SOURCES
    src/items/Item.cpp
    src/items/Weapon.cpp
    src/entities/Entity.cpp
    src/entities/Player.cpp
)

set(SERVER_MAIN     src/main.cpp)
set(CLI_MAIN        src/cli/cli_main.cpp)
set(GUI_MAIN        src/gui/gui_main.cpp)

set(SERVER_SOURCES  ${SERVER_MAIN} ${COMMON_SOURCES})

set(CLI_SOURCES     ${CLI_MAIN}    ${COMMON_SOURCES})

set(GUI_SOURCES
    ${GUI_MAIN}
    ${COMMON_SOURCES}
    src/gui/entities/VisualEntity.cpp
)

# -------------#
#  Executables
# -------------#

# 1. Server TCP
add_executable(tap_server ${SERVER_SOURCES})
target_link_libraries(tap_server PRIVATE
    project_warnings
    Threads::Threads
    yaml-cpp
    nlohmann_json::nlohmann_json
)

# 2. Client CLI
add_executable(tap_cli_client ${CLI_SOURCES})
target_link_libraries(tap_cli_client PRIVATE
    project_warnings
    Threads::Threads
    nlohmann_json::nlohmann_json
)

# 3. Client GUI
add_executable(tap_gui_client ${GUI_SOURCES})
target_link_libraries(tap_gui_client PRIVATE
    project_warnings
    Threads::Threads
    nlohmann_json::nlohmann_json
    raylib
)
