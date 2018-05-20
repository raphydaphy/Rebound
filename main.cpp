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
            0.5f, -0.5f, 0
    };

    static const GLint indices[] = {
            0, 1, 2, 2, 0, 3
    };

    VertexArray vao = VertexArray().bind().storeIndices(indices, sizeof(indices)).createAttribute(0, vertices, sizeof(vertices), 3).unbind();

    StaticObjectShader shader;

    while (disp::open())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        vao.bind({0}).indices.bind();
        shader.bind();
        glDrawElements(GL_TRIANGLES, vao.getIndicesLength(), GL_UNSIGNED_INT, nullptr);
        shader.unbind();
        vao.unbind({0}).indices.unbind();

        disp::update();
    }

    shader.cleanup();
    vao.del();
    disp::destroy();

    return 0;
}