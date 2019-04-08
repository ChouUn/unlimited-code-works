cmake_minimum_required(VERSION 3.13)
project(unlimited_code_works)

set(CMAKE_CXX_STANDARD 11)

file(GLOB source_files "src/*.cpp")

include_directories("libs/")

add_executable(unlimited_code_works ${source_files})
