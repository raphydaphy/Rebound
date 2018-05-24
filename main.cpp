#include "main.hpp"

VertexArray *vao;
StaticObjectShader *shader;

glm::mat4 *projection;
glm::mat4 *view;
glm::mat4 *model;

int main()
{
    if (!core::initDisplay())
    {
        return 1;
    }

    core::initTimer();

    glClearColor(0.5f, 0.5f, 0.5f, 1);

    static const GLfloat vertices[] = {
            -1, -1, 0,
            -1, 1, 0,
            1, 1, 0,
            1, -1, 0
    };

    static const GLint indices[] = {
            0, 1, 2, 2, 0, 3
    };

    vao = new VertexArray();
    vao->bind().storeIndices(indices, sizeof(indices)).createAttribute(0, vertices, sizeof(vertices), 3).unbind();
    shader = new StaticObjectShader();

    // Projection matrix : 45° Field of View, 4:3 ratio, core range : 0.1 unit <-> 100 units
    projection = new glm::mat4();
    *projection = glm::perspective(glm::radians(45.0f), (float) core::getDisplayWidth() / core::getDisplayHeight(), 0.1f, 100.0f);

    view = new glm::mat4();
    *view = glm::lookAt(
            glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    model = new glm::mat4(1.0f);

    shader->bind();
    shader->projection.load(*projection);
    shader->view.load(*view);
    shader->unbind();

    const int TARGET_FPS = 120;
    const int TARGET_TPS = 20;

    float delta = 0;
    float accumulator = 0;
    float interval = 1.0f / TARGET_TPS;
    float alpha = 0;

    while (core::displayOpen())
    {
        delta = core::getDeltaTime();
        accumulator += delta;

        while (accumulator >= interval)
        {
            update(1.0f / TARGET_TPS);
            core::updateTPS();
            accumulator -= interval;
        }
        alpha = accumulator / interval;
        render(alpha);

        core::updateFPS();
        core::updateTimer();

        std::cout << "h" << std::endl;
        core::syncTimer(TARGET_FPS);
        std::cout << "y" << std::endl;
    }

    shader->cleanup();
    vao->del();
    core::destroyDisplay();

    return 0;
}

void update(float delta)
{

}

void render(float alpha)
{
    glClear(GL_COLOR_BUFFER_BIT);

    vao->bind({0}).indices.bind();
    shader->bind();

    shader->model.load(*model);

    glDrawElements(GL_TRIANGLES, vao->getIndicesLength(), GL_UNSIGNED_INT, nullptr);

    shader->unbind();
    vao->unbind({0}).indices.unbind();

    *model = glm::translate(*model, glm::vec3(0.01f, 0.001f, 0.0f));

    core::updateDisplay();
}
