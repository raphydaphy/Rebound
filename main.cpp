#include "main.h"

int main()
{
    /* ========================================
     *          Display Initialization
     * ======================================== */
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // anti-aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(1080, 720, "Automania", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    if (gl3wInit() != GL3W_OK)
    {
        std::cout << "Unable to initialize GL3W" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    /* ========================================
     *          OpenGL Object Setup
     * ======================================== */

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    static const GLfloat vertices[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    StaticObjectShader shader;


    /* ========================================
     *                Game Loop
     * ======================================== */
    do {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();

        // enable the first buffer within the vbo
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(/*attribute 0 in the vao*/0, /*3 dimensions per vertex*/3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        shader.unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}
/*
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
*/