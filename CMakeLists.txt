

cmake_minimum_required(VERSION 3.10)
project(LearnCPP)

set(CMAKE_CXX_STANDARD 11)
set(LIBRARIES_DIR "lib")

# Including GLFW
add_subdirectory("${LIBRARIES_DIR}/glfw")
include_directories("${LIBRARIES_DIR}/glfw/include")

add_subdirectory("lib/glm")
include_directories("${LIBRARIES_DIR}/glw/glw")

add_executable(${PROJECT_NAME} main.cpp main.hpp engine/core/display.cpp engine/core/display.hpp engine/gl/VertexBuffer.cpp engine/gl/VertexBuffer.hpp engine/gl/VertexArray.cpp engine/gl/VertexArray.hpp engine/gl/Uniform.cpp engine/gl/Uniform.hpp engine/shader/ShaderProgram.cpp engine/shader/ShaderProgram.hpp engine/shader/impl/StaticObjectShader.cpp engine/shader/impl/StaticObjectShader.hpp engine/core/timer.cpp engine/core/timer.hpp engine/core/loader.cpp engine/core/loader.hpp engine/core/pico.cpp engine/core/pico.hpp engine/scene/Model.cpp engine/scene/Model.hpp)

# Linking GLFW
target_link_libraries(${PROJECT_NAME} "glfw" ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} "glm" ${GLM_LIBRARIES})

# gl3w
set(GL3W_DIR "${LIBRARIES_DIR}/gl3w")
add_library("gl3w" "${GL3W_DIR}/src/gl3w.c")
target_include_directories("gl3w" PRIVATE "${GL3W_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GL3W_DIR}/include")
target_link_libraries(${PROJECT_NAME} "gl3w" "${CMAKE_DL_LIBS}")

