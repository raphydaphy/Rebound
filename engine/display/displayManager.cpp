#include "displayManager.h"

namespace disp
{
    GLFWwindow *window;

    bool init()
    {
        if (!glfwInit())
        {
            std::cerr << "Unable to initialize GLFW :(" << std::endl;
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(1280, 720, "LearnCPP", nullptr, nullptr);

        if (!window)
        {
            std::cerr << "Unable to create GLFW window :(" << std::endl;
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGL())
        {
            std::cerr << "Unable to initialize glad :(" << std::endl;
            glfwDestroyWindow(window);
            glfwTerminate();
            return false;
        }

        std::cout << "Initialized GLFW successfully with version " << glfwGetVersionString() << std::endl;

        return true;
    }

    void destroy()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    bool open()
    {
        return !glfwWindowShouldClose(window);
    }

    void update()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}