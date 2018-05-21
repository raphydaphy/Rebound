

cmake_minimum_required(VERSION 3.10)
project(LearnCPP)

set(CMAKE_CXX_STANDARD 11)
set(LIBRARIES_DIR "lib")

# Including GLFW
add_subdirectory("${LIBRARIES_DIR}/glfw")
include_directories("${LIBRARIES_DIR}/glfw/include")

add_subdirectory("lib/glm")
include_directories("${LIBRARIES_DIR}/glw/glw")

add_executable(${PROJECT_NAME} main.cpp main.h engine/display/displayManager.cpp engine/display/displayManager.h engine/gl/VertexBuffer.cpp engine/gl/VertexBuffer.h engine/gl/VertexArray.cpp engine/gl/VertexArray.h engine/gl/uniform/Uniform.cpp engine/gl/uniform/Uniform.h engine/shader/ShaderProgram.cpp engine/shader/ShaderProgram.h engine/shader/impl/StaticObjectShader.cpp engine/shader/impl/StaticObjectShader.h)

# Linking GLFW
target_link_libraries(${PROJECT_NAME} "glfw" ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} "glm" ${GLM_LIBRARIES})

# gl3w
set(GL3W_DIR "${LIBRARIES_DIR}/gl3w")
add_library("gl3w" "${GL3W_DIR}/src/gl3w.c")
target_include_directories("gl3w" PRIVATE "${GL3W_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GL3W_DIR}/include")
target_link_libraries(${PROJECT_NAME} "gl3w" "${CMAKE_DL_LIBS}")

