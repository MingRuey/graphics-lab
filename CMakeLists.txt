cmake_minimum_required(VERSION 3.20)
project(graphics-lab)

set(CMAKE_CXX_STANDARD 14)

# glfw
include_directories(lib)
add_library(glfw STATIC IMPORTED model/ObjLoader.cpp model/ObjLoader.h camera/camera.h camera/camera.cpp)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include")

#freetype
add_library(freetype STATIC IMPORTED)
set_target_properties(freetype PROPERTIES
	IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/freetype.lib"
	INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
)


#glm
include_directories(include/glm)

add_executable(main
        glad.c
        model/ObjLoader.cpp
        shader/ShaderLoader.cpp
		camera/camera.cpp
		freetype/FreetypeManager.cpp
        main.cpp)

target_link_libraries(main glfw freetype)
