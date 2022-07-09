cmake_minimum_required(VERSION 3.22.1)
project(TensionEngine_Core VERSION 0.0.1 LANGUAGES C CXX)

add_definitions(-DTENSION_CORE_EXPORT)
aux_source_directory(src TENSION_CORE_SRC)
include_directories(../glew/include/)

add_library(TensionCoreStatic STATIC ${TENSION_CORE_SRC})
target_include_directories(TensionCoreStatic PRIVATE include)
target_link_libraries(TensionCoreStatic LINK_PUBLIC glew32s)

add_library(TensionCore SHARED ${TENSION_CORE_SRC})
target_include_directories(TensionCore PRIVATE include)
target_link_libraries(TensionCore LINK_PUBLIC glew32)

install(TARGETS TensionCoreStatic TensionCore)
install(DIRECTORY include/tension TYPE INCLUDE)