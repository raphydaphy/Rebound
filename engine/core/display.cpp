#include "display.hpp"
#include "../../main.hpp"

namespace core
{
    GLFWwindow *window;

    int prevWidth = 0;
    int prevHeight = 0;

    bool initDisplay()
    {
        glfwSetErrorCallback(errorCallback);

        if (!glfwInit())
        {
            std::cerr << "Unable to initialize GLFW :(" << std::endl;
            return false;
        }


        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(1280, 720, "Automania", nullptr, nullptr);

        if (!window)
        {
            std::cerr << "Unable to create GLFW window :(" << std::endl;
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(0);

        std::cout << "Initialized GLFW successfully with version " << glfwGetVersionString() << std::endl;

        if (gl3wInit())
        {
            std::cerr << "Unable to initialize gl3w :(" << std::endl;
            glfwDestroyWindow(window);
            glfwTerminate();
            return false;
        }

        if (!gl3wIsSupported(4, 0))
        {
            std::cerr << "OpenGL 4.0 is not supported by your system!" << std::endl;
            return false;
        }

        std::cout << "Initialized GL3W with OpenGL version " << glGetString(GL_VERSION) << " and GLSL version " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        return true;
    }

    void destroyDisplay()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    bool displayOpen()
    {
        return !glfwWindowShouldClose(window);
    }

    bool displayResized()
    {
        return prevWidth != getDisplayWidth() || prevHeight != getDisplayHeight();
    }

    void updateDisplay()
    {
        prevWidth = getDisplayWidth();
        prevHeight = getDisplayHeight();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    int getDisplayWidth()
    {
        int width = 0;
        glfwGetWindowSize(window, &width, nullptr);
        return width;
    }

    int getDisplayHeight()
    {
        int height = 0;
        glfwGetWindowSize(window, nullptr, &height);
        return height;
    }

    void errorCallback(int error, const char* description)
    {
        std::cerr << "GLF5W Error " << error << std::endl << description << std::endl;
    }
}