#include "main.hpp"

StaticModel *acacia_1;
StaticModel *acacia_2;
StaticModel *acacia_3;

StaticObjectShader *shader;

glm::mat4 *projection;
glm::mat4 *view;

glm::mat4 *model_acacia_base;
glm::mat4 *model_acacia_translated;

glm::vec3 *rectPos;
glm::vec3 *prevRectPos;

int main()
{
    if (!core::initDisplay("Rebound")) return 1;

    core::initTimer();

    glClearColor(0.5f, 0.5f, 0.5f, 1);

    acacia_1 = new StaticModel("model/acacia_tree_1");
    acacia_2 = new StaticModel("model/acacia_tree_2");
    acacia_3 = new StaticModel("model/acacia_tree_3");

    shader = new StaticObjectShader();

    Texture atlas = Texture("texture/atlas");
    atlas.bind();

    projection = new glm::mat4();

    view = new glm::mat4();
    *view = glm::lookAt(glm::vec3(1,2,-10), glm::vec3(0,1,0), glm::vec3(0,1,0));

    float sunBrightness = 0.8f;
    Light sun(glm::vec3(50000, 100000, 50000), glm::vec3(sunBrightness, sunBrightness, sunBrightness));

    glm::vec3 skyColor(0.5, 0.5, 0.5);

    model_acacia_base = new glm::mat4(1.0f);
    model_acacia_translated = new glm::mat4(1.0f);

    rectPos = new glm::vec3(10, 0, 0);
    prevRectPos = new glm::vec3(10, 0, 0);

    shader->bind();
    shader->view.load(*view);
    shader->loadLight(sun, 0);
    shader->sky_color.load(skyColor);
    shader->unbind();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

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

    glDisable(GL_DEPTH_TEST);

    shader->cleanup();

    acacia_1->del();
    acacia_2->del();

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->bind();

    if (core::displayResized())
    {
        *projection = glm::perspective(glm::radians(45.0f), (float) core::getDisplayWidth() / core::getDisplayHeight(), 0.1f, 100.0f);
        shader->projection.load(*projection);

        glViewport(0, 0, core::getDisplayWidth(), core::getDisplayHeight());
    }


    acacia_1->bind();
    *model_acacia_base = glm::scale(glm::mat4(1), glm::vec3(0.25f));
    *model_acacia_base = glm::translate(*model_acacia_base, glm::vec3(prevRectPos->x + alpha * (rectPos->x - prevRectPos->x), 0, 0));
    shader->model.load(*model_acacia_base);
    glDrawArrays(GL_TRIANGLES, 0, acacia_1->getVerticesLength());
    acacia_1->unbind();

    acacia_2->bind();
    *model_acacia_translated = glm::translate(*model_acacia_base, glm::vec3(-15, 0, 0));
    shader->model.load(*model_acacia_translated);
    glDrawArrays(GL_TRIANGLES, 0, acacia_2->getVerticesLength());
    acacia_2->unbind();

    acacia_3->bind();
    *model_acacia_translated = glm::translate(*model_acacia_translated, glm::vec3(-18, 0, 0));
    shader->model.load(*model_acacia_translated);
    glDrawArrays(GL_TRIANGLES, 0, acacia_3->getVerticesLength());
    acacia_3->unbind();

    shader->unbind();


    core::updateDisplay();
}