cmake_minimum_required(VERSION 3.10)
project (numeric_images VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
add_compile_options("-march=native")

find_package(blaze REQUIRED)
add_library(blaze_target INTERFACE)
target_link_libraries(blaze_target INTERFACE blaze::blaze)

add_executable(trivial_matrices.x src/main_trivial_matrices.cpp)
target_link_libraries(trivial_matrices.x blaze_target)


add_subdirectory(test)
