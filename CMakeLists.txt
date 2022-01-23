cmake_minimum_required(VERSION 3.20)
project(graphics-lab)

set(CMAKE_CXX_STANDARD 14)

# glfw
include_directories(lib)
add_library(glfw STATIC IMPORTED model/ObjLoader.cpp model/ObjLoader.h)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include")

#glm
include_directories(include/glm)

add_executable(main
        glad.c
        model/ObjLoader.cpp
        shader/ShaderLoader.cpp
        main.cpp)

target_link_libraries(main glfw)
