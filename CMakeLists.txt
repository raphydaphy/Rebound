cmake_minimum_required(VERSION 3.10)
project(LearnCPP)

set(CMAKE_CXX_STANDARD 11)
set(LIBRARIES_DIR "lib")

# Including GLFW
add_subdirectory("${LIBRARIES_DIR}/glfw")
include_directories("${LIBRARIES_DIR}/glfw/include")

add_executable(${PROJECT_NAME} main.cpp main.h engine/display/displayManager.cpp engine/display/displayManager.h)

# Linking GLFW
target_link_libraries(${PROJECT_NAME} "glfw" ${GLFW_LIBRARIES})

# glad
set(GLAD_DIR "${LIBRARIES_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")