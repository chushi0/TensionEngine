cmake_minimum_required(VERSION 3.22.1)
project(TensionEngine_Test VERSION 0.0.1 LANGUAGES C CXX)

add_definitions(-DTENSION_CORE_STATIC)
include_directories(../core/include/)
include_directories(../glew/include/)

aux_source_directory(src TENSION_TEST_SRC)
add_executable(TensionTest ${TENSION_TEST_SRC})
target_link_libraries(TensionTest TensionCoreStatic)