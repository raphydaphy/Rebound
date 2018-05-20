#include "main.h"

int main()
{
    if (!disp::init())
    {
        return 1;
    }

    glClearColor(0.5f, 0.5f, 0.5f, 1);

    static const GLfloat vertices[] = {
            -0.5f, -0.5f, 0,
            -0.5f, 0.5f, 0,
            0.5f, 0.5f, 0,
            0.5f, 0.5f, 0,
            -0.5f, -0.5f, 0,
            0.5f, -0.5f, 0
    };

    VertexArray vao = VertexArray().bind().createAttribute(0, vertices, sizeof(vertices), 3).unbind();

    StaticObjectShader shader;

    while (disp::open())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        vao.bind({0});
        shader.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        shader.unbind();
        vao.unbind({0});

        disp::update();
    }

    shader.cleanup();
    vao.del();
    disp::destroy();

    return 0;
}