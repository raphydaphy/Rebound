#include "main.h"

int main()
{


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

    VertexArray vao = VertexArray().bind().createAttribute(0, vertices, sizeof(vertices), 3).unbind();

    while (disp::open())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        vao.bind({0});
        glDrawArrays(GL_TRIANGLES, 0, vao.getIndicesLength() / 3);
        vao.unbind({0});

        disp::update();
    }

    vao.del();
    disp::destroy();

    return 0;
}
