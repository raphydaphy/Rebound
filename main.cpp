#include "main.hpp"

VertexArray *vao;
StaticObjectShader *shader;

glm::mat4 *projection;
glm::mat4 *view;
glm::mat4 *model;

glm::vec3 *rectPos;
glm::vec3 *prevRectPos;

int verticesLength = 0;

int main()
{
    if (!core::initDisplay("Rebound")) return 1;

    core::initTimer();

    glClearColor(0.5f, 0.5f, 0.5f, 1);

    Model acacia_1 = core::loadOBJ("../res/model/acacia_tree_1.obj");
    verticesLength = acacia_1.verticesArray.size();
    std::cout << "Indices: " << acacia_1.indicesArray.size() << " Vertices: " << acacia_1.verticesArray.size() << std::endl;
    vao = new VertexArray();

    std::cout << "v0" << acacia_1.texturesArray[0].x << std::endl;
    vao->bind();
    vao->storeIndices(&acacia_1.indicesArray[0], acacia_1.indicesArray.size())
            .createAttribute(0, &acacia_1.verticesArray[0], acacia_1.verticesArray.size() * sizeof(glm::vec3), 3)
            .createAttribute(1, &acacia_1.texturesArray[0], acacia_1.texturesArray.size() * sizeof(glm::vec2), 2).unbind();
    shader = new StaticObjectShader();

    // temporary, will create a class for it later

    const char* filename = "../res/texture/atlas.png";

    //load and decode
    std::vector<unsigned char> buffer, image;
    core::loadPNG(buffer, filename);
    GLsizei width, height;
    int error = pico::decodePNG(image, width, height, buffer.empty() ? nullptr : &buffer[0], (unsigned long)buffer.size(), true);

    //if there's an error, display it
    if(error != 0)
    {
        std::cout << "error: " << error << std::endl;
    }

    GLuint texID;

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(image[0]));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    projection = new glm::mat4();

    view = new glm::mat4();
    *view = glm::lookAt(glm::vec3(4,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));

    model = new glm::mat4(1.0f);

    rectPos = new glm::vec3(0);
    prevRectPos = new glm::vec3(0);

    shader->bind();
    shader->view.load(*view);
    shader->unbind();

    while (core::displayOpen())
    {
        while (core::shouldTick())
        {
            update(1.0f / core::getTargetTPS());
            core::updateTPS();
        }

        render(core::getAlphaTime());

        core::updateFPS();
    }

    shader->cleanup();
    vao->del();
    core::destroyDisplay();

    return 0;
}

void update(float delta)
{
    prevRectPos->x = rectPos->x;
    rectPos->x += 0.01f;
}

void render(float alpha)
{
    glClear(GL_COLOR_BUFFER_BIT);

    vao->bind({0, 1}).indices.bind();
    shader->bind();

    if (core::displayResized())
    {
        *projection = glm::perspective(glm::radians(45.0f), (float) core::getDisplayWidth() / core::getDisplayHeight(), 0.1f, 100.0f);
        shader->projection.load(*projection);

        glViewport(0, 0, core::getDisplayWidth(), core::getDisplayHeight());
    }

    *model = glm::scale(glm::mat4(1), glm::vec3(0.25f));
    *model = glm::translate(*model, glm::vec3(prevRectPos->x + alpha * (rectPos->x - prevRectPos->x), 0, 0));
    shader->model.load(*model);

    // glDrawElements(GL_TRIANGLES, vao->getIndicesLength(), GL_UNSIGNED_INT, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, verticesLength);

    shader->unbind();
    vao->unbind({0, 1}).indices.unbind();

    core::updateDisplay();
}