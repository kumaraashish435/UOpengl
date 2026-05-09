cmake_minimum_required(VERSION 3.16)

project(app LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLAD
add_library(glad STATIC dependencies/glad/src/glad.c)
target_include_directories(glad PUBLIC 
    dependencies/glad/include 
    dependencies/stb 
    Includes
)

# shader directory
# shader files
file(GLOB SHADER_FILES "${CMAKE_SOURCE_DIR}/shaders/*.glsl")

foreach(shader ${SHADER_FILES})
    configure_file(${shader} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

file(GLOB TEXTURES "${CMAKE_SOURCE_DIR}/textures/*")

foreach(tex ${TEXTURES})
    configure_file(${tex} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

# App
add_executable(${PROJECT_NAME} 
    src/Application.cpp
    src/Shader.cpp 
    src/Window.cpp
    src/EBO.cpp
    src/VAO.cpp
    src/VBO.cpp
    src/Texture.cpp
    src/Camera.cpp 
)

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    glfw
    OpenGL::GL
    glm::glm
)