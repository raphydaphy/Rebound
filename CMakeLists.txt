cmake_minimum_required(VERSION 3.10)
project(Rebound)

set(CMAKE_CXX_STANDARD 17)
set(DL_LIBRARIES_DIR "${CMAKE_BINARY_DIR}/dl_lib")
set(LIBRARIES_DIR "lib")

include(ExternalProject)

#ExternalProject_Add(GLFW URL "https://github.com/glfw/glfw/archive/3.2.1.tar.gz" PREFIX "${DL_LIBRARIES_DIR}/install/glfw" CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${DL_LIBRARIES_DIR}/glfw")
ExternalProject_Add(GLM URL "https://github.com/g-truc/glm/archive/0.9.9.0.tar.gz" PREFIX "${DL_LIBRARIES_DIR}/install/glm" CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${DL_LIBRARIES_DIR}/glm")

include_directories("${DL_LIBRARIES_DIR}/glm/include")

find_package(glfw3 "3.0.0" QUIET)
# Check if the library exists after our find_package() call.
# Note that if this were a regular FindXXX module, we'd check "if NOT GLFW_FOUND" instead.
if(NOT TARGET glfw)
    # Update submodules automatically
    # Note that this can fail silenty if Git isn't in the $PATH
    execute_process(COMMAND git submodule update --init --recursive
            # Tell it where to run the submodule update
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            # Here we save any failures to use later
            ERROR_VARIABLE _glfw_submod_update
            )
    # Fail if any errors while updating submodule...
    # Or if the git submodule wasn't initialized
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/glfw/CMakeLists.txt" AND NOT _glfw_submod_update)
        # Fail since we can't update and the submodule hasn't be initialized
        message(FATAL_ERROR "Run \"git submodule update --init --recursive before building")
    endif()
    # Skip building unnecssary stuff for a speed increase
    # These variables are checked in the upstream submodule
    foreach(_glfw_option "GLFW_BUILD_TESTS" "GLFW_BUILD_EXAMPLES" "GLFW_BUILD_DOCS")
        # Let the user define these if they want them for some reason...
        # This avoids "stomping" of any other projects settings
        if(NOT ${_glfw_option})
            set(${_glfw_option} false)
        endif()
    endforeach()
    #[[
    Build the project as part of ours
    This will bring the library into scope to be used below
    Note its just the name of the submodule directory
    ]]
    add_subdirectory(glfw)
endif()

add_executable(${PROJECT_NAME} main.cpp main.hpp engine/core/display.cpp engine/core/display.hpp engine/gl/VertexBuffer.cpp engine/gl/VertexBuffer.hpp engine/gl/VertexArray.cpp engine/gl/VertexArray.hpp engine/gl/Uniform.cpp engine/gl/Uniform.hpp engine/shader/ShaderProgram.cpp engine/shader/ShaderProgram.hpp engine/shader/impl/StaticShader.cpp engine/shader/impl/StaticShader.hpp engine/core/timer.cpp engine/core/timer.hpp engine/core/loader.cpp engine/core/loader.hpp engine/lib/pico.cpp engine/lib/pico.hpp engine/scene/Model.cpp engine/scene/Model.hpp engine/scene/Texture.cpp engine/scene/Texture.hpp engine/scene/Light.cpp rebound/terrain/marching.cpp rebound/terrain/marching.hpp rebound/terrain/Biome.cpp rebound/terrain/Biome.hpp rebound/terrain/Terrain.cpp rebound/terrain/Terrain.hpp engine/core/util.cpp engine/core/util.hpp engine/lib/OpenSimplexNoise.hpp rebound/res/OBJModels.hpp rebound/res/OBJModels.cpp)


target_link_libraries(${PROJECT_NAME} glfw)

# Defines standardized installation paths depending on the system
include(GNUInstallDirs)
# Install the binary if the user runs the install command
install(TARGETS ${PROJECT_NAME}
        # "RUNTIME" here is technically pointless, but still good practice
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )

#target_include_directories(${PROJECT_NAME} PRIVATE "${DL_LIBRARIES_DIR}/glfw/include")
#if (WIN32)
#endif()

#target_link_libraries(${PROJECT_NAME} "${CMAKE_BINARY_DIR}/dl_lib/glfw/lib/libglfw3.a")

# gl3w
set(GL3W_DIR "${LIBRARIES_DIR}/gl3w")
add_library("gl3w" "${GL3W_DIR}/src/gl3w.c")
target_include_directories("gl3w" PRIVATE "${GL3W_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GL3W_DIR}/include")
target_link_libraries(${PROJECT_NAME} "gl3w" "${CMAKE_DL_LIBS}")