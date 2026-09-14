cmake_minimum_required(version 3.16)
project(The_Answer_Protocol)

# Norm
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(includes)

add_executable(tap_server <fichiers_sources>)
add_executable(tap_cli_client <fichiers_sources>)
add_executable(tap_gui_client <fichiers_sources>)

target_compile_options(tap_server PRIVATE -Wall -Wextra -Werror)
target_compile_options(tap_cli_client PRIVATE -Wall -Wextra -Werror)
target_compile_options(tap_gui_client PRIVATE -Wall -Wextra -Werror)
