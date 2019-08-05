cmake_minimum_required(VERSION 3.13)
project(unlimited_code_works)

add_compile_options(-g)
add_compile_options(-lm)

add_compile_options(-Wall)
add_compile_options(-Werror)
add_compile_options(-Wshadow)
add_compile_options(-Wfloat-equal)

add_compile_options(-pedantic)
add_compile_options(-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC)

add_link_options(-fsanitize=address)
add_compile_options(-fsanitize=address)
#add_link_options(-fsanitize=undefined -fno-sanitize-recover)
#add_compile_options(-fsanitize=undefined -fno-sanitize-recover)
add_compile_options(-fstack-protector)

set(CMAKE_CXX_STANDARD 11)

file(GLOB source_files "src/*.cpp")

include_directories("libs/")

add_executable(unlimited_code_works ${source_files})
