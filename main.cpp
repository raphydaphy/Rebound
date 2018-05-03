#include "main.h"

int main()
{
    glfwSetErrorCallback(errorCallback);

    if (!disp::init())
    {
        return 1;
    }

    glClearColor(0.5f, 0.5f, 0.5f, 1);

    float vertices[] = {
            -0.5f, 0.5f, 0,
            -0.5f, -0.5f, 0,
            0.5f, -0.5f, 0,
            0.5f, -0.5f, 0,
            0.5f, 0.5f, 0,
            -0.5f, 0.5f, 0
    };

    VertexArray vao = VertexArray().bind().createAttribute(0, vertices, sizeof(vertices) / sizeof(vertices[0]), 3).unbind();

    while (disp::open())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        vao.bind({0});
        glDrawArrays(GL_TRIANGLES, 0, vao.getIndicesLength());
        vao.unbind({0});

        disp::update();
    }

    vao.del();
    disp::destroy();

    return 0;
}

void errorCallback(int error, const char* description)
{
    std::cerr << "GLF5W Error " << error << std::endl << description << std::endl;
}

