cmake_minimum_required(VERSION 3.26.3)
project(bitcalc VERSION 1.0)

# set c++ std
add_library(compile_flags INTERFACE)
target_compile_features(compile_flags INTERFACE cxx_std_17)

# add warning flags
set(is_gcc_like "$<COMPILE_LANG_AND_ID:CXX,Clang,GNU>")
target_compile_options(compile_flags INTERFACE "$<${is_gcc_like}:-Wall;-Wextra;-Werror;>")

# set binary output dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# build src
add_subdirectory(src)
