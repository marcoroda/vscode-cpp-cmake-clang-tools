cmake_minimum_required(VERSION 3.14)
project(vscode_clang_tools)

# For clang-tidy analyses 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Cpp statndard
set(CMAKE_CXX_STANDARD 17)

# threads
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(cpp_clang_tools main.cpp)
add_executable(thread thread.cpp)
add_executable(thread_2 thread_2.cpp)

include_directories(Calc_lib)
include_directories(AudioStream_lib)
add_subdirectory(Calc_lib)
add_subdirectory(AudioStream_lib)

target_link_libraries(cpp_clang_tools Calc_lib AudioStream_lib)