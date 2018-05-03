#include "main.h"

int main()
{
    glfwSetErrorCallback(errorCallback);

    if (!disp::init())
    {
        return 1;
    }

    glClearColor(0.5f, 0.5f, 0.5f, 1);

    while (disp::open())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        disp::update();
    }

    disp::destroy();

    return 0;
}

void errorCallback(int error, const char* description)
{
    std::cerr << "GLF5W Error " << error << std::endl << description << std::endl;
}

