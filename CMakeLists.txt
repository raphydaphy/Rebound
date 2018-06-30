cmake_minimum_required(VERSION 3.10)
project(Rebound)

set(CMAKE_CXX_STANDARD 17)
set(DL_LIBRARIES_DIR "${CMAKE_BINARY_DIR}/dl_lib")
set(LIBRARIES_DIR "lib")

include(ExternalProject)

# get GLFW

ExternalProject_Add(GLFW URL "https://github.com/glfw/glfw/archive/3.2.1.tar.gz" CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${DL_LIBRARIES_DIR}/_glfw_install")
ExternalProject_Add(GLM URL "https://github.com/g-truc/glm/archive/0.9.9.0.tar.gz" CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${DL_LIBRARIES_DIR}/_glm_install")
ExternalProject_Add(DISCORD_RPC URL "https://github.com/discordapp/discord-rpc/archive/v3.3.0.tar.gz" CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${DL_LIBRARIES_DIR}/_discord_rpc_install")

# Including GLM (old)
#add_subdirectory("${CMAKE_BINARY_DIR}/GLM-prefix/src/GLM")
#include_directories("${CMAKE_BINARY_DIR}/GLM-prefix/src/GLM/glm")

include_directories("${DL_LIBRARIES_DIR}/_glm_install/include")

add_executable(${PROJECT_NAME} main.cpp main.hpp engine/core/display.cpp engine/core/display.hpp engine/gl/VertexBuffer.cpp engine/gl/VertexBuffer.hpp engine/gl/VertexArray.cpp engine/gl/VertexArray.hpp engine/gl/Uniform.cpp engine/gl/Uniform.hpp engine/shader/ShaderProgram.cpp engine/shader/ShaderProgram.hpp engine/shader/impl/StaticShader.cpp engine/shader/impl/StaticShader.hpp engine/core/timer.cpp engine/core/timer.hpp engine/core/loader.cpp engine/core/loader.hpp engine/lib/pico.cpp engine/lib/pico.hpp engine/scene/Model.cpp engine/scene/Model.hpp engine/scene/Texture.cpp engine/scene/Texture.hpp engine/scene/Light.cpp rebound/terrain/marching.cpp rebound/terrain/marching.hpp rebound/terrain/Biome.cpp rebound/terrain/Biome.hpp rebound/terrain/Terrain.cpp rebound/terrain/Terrain.hpp engine/core/util.cpp engine/core/util.hpp engine/lib/OpenSimplexNoise.hpp rebound/res/OBJModels.hpp rebound/res/OBJModels.cpp engine/core/discord.cpp engine/core/discord.hpp)

# Linking
message(STATUS ${GLM_LIBRARIES})
message(STATUS HELLOTHERE)
#target_link_libraries(${PROJECT_NAME} "glm" ${GLM_LIBRARIES})

# Include GLFW
target_include_directories(${PROJECT_NAME} PRIVATE "${DL_LIBRARIES_DIR}/_glfw_install/include")
if (WIN32)
    target_link_libraries(${PROJECT_NAME} "${CMAKE_BINARY_DIR}/dl_lib/_glfw_install/lib/glfw3.lib")
endif()

# Include DiscordRPC
target_include_directories(${PROJECT_NAME} PRIVATE "${DL_LIBRARIES_DIR}/_discord_rpc_install/include")
if (WIN32)
    target_link_libraries(${PROJECT_NAME} "${CMAKE_BINARY_DIR}/dl_lib/_discord_rpc_install/lib/discord-rpc.lib")
endif()

# gl3w
set(GL3W_DIR "${LIBRARIES_DIR}/gl3w")
add_library("gl3w" "${GL3W_DIR}/src/gl3w.c")
target_include_directories("gl3w" PRIVATE "${GL3W_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GL3W_DIR}/include")
target_link_libraries(${PROJECT_NAME} "gl3w" "${CMAKE_DL_LIBS}")