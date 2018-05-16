#include "main.h"

int main()
{


    if (!disp::init())
    {
        return 1;
    }

    glClearColor(0.5f, 0.5f, 0.5f, 1);

    float vertices[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            -0.5f, 0.5f,
            0.5f, 0.5f,
    };

    int indices[] = {
            0, 1, 3,
            3, 1, 2
    };

    //.storeIndices(indices, sizeof(indices) / sizeof(indices[0]))
    VertexArray vao = VertexArray().bind().createAttribute(0, vertices, sizeof(vertices) / sizeof(vertices[0]), 2).unbind();

    StaticObjectShader shader;

    while (disp::open())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        vao.bind({0});
        shader.bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
      //  glDrawElements(GL_TRIANGLE_STRIP, vao.getIndicesLength(), GL_UNSIGNED_INT, nullptr);
        shader.unbind();
        vao.unbind({0});

        disp::update();
    }

    shader.cleanup();
    vao.del();
    disp::destroy();

    return 0;
}
