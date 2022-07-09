cmake_minimum_required(VERSION 3.22.1)
project(glew VERSION 2.1.0 LANGUAGES C)

add_definitions(-DGLEW_NO_GLU)
add_definitions(-DGLEW_BUILD)
aux_source_directory(src GLEW_SRC)

find_package(OpenGL REQUIRED)

add_library(glew32s STATIC ${GLEW_SRC})
target_include_directories(glew32s PRIVATE include)
target_link_libraries(glew32s ${OPENGL_LIBRARIES})

add_library(glew32 SHARED ${GLEW_SRC})
target_include_directories(glew32 PRIVATE include)
target_link_libraries(glew32 LINK_PUBLIC ${OPENGL_LIBRARIES})

install(TARGETS glew32s glew32)
install(DIRECTORY include/GL TYPE INCLUDE)