cmake_minimum_required(VERSION 3.14)
project(vscode_clang_tools)

# For clang-tidy analyses 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Cpp statndard
set(CMAKE_CXX_STANDARD 14)

add_executable(cpp_clang_tools main.cpp)

include_directories(Calc_lib)
add_subdirectory(Calc_lib)

target_link_libraries(cpp_clang_tools Calc_lib)