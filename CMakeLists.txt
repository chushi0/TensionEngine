cmake_minimum_required(VERSION 3.22.1)
project(TensionEngine VERSION 0.0.1)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_subdirectory(glew)
add_subdirectory(core)
add_subdirectory(test)