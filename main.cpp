#include "main.hpp"

TexturedStaticModel *acacia_1;
TexturedStaticModel *acacia_2;
TexturedStaticModel *acacia_3;

StaticTexturedShader *texturedShader;
StaticColoredShader *coloredShader;

Terrain *terrain;

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
    core::setResourceDirectory("../rebound/res/");
    core::initSeed(98);

    biomes::init();

    glClearColor(0.5f, 0.5f, 0.5f, 1);

    acacia_1 = new TexturedStaticModel("model/acacia_tree_1");
    acacia_2 = new TexturedStaticModel("model/acacia_tree_2");
    acacia_3 = new TexturedStaticModel("model/acacia_tree_3");

    terrain = new Terrain(0, 0, 0);

    texturedShader = new StaticTexturedShader();
    coloredShader = new StaticColoredShader();

    Texture atlas = Texture("texture/atlas");
    atlas.bind();

    projection = new glm::mat4();

    view = new glm::mat4();
    *view = glm::lookAt(glm::vec3(1,2,-10), glm::vec3(0,1,0), glm::vec3(0,1,0));

    float sunBrightness = 1;
    Light sun(glm::vec3(-10, 8, -10), glm::vec3(sunBrightness, sunBrightness, sunBrightness));

    glm::vec3 skyColor(0.5, 0.5, 0.5);

    model_acacia_base = new glm::mat4(1.0f);
    model_acacia_translated = new glm::mat4(1.0f);

    rectPos = new glm::vec3(-15, 0, 0);
    prevRectPos = new glm::vec3(-15, 0, 0);

    texturedShader->bind();
    texturedShader->view.load(*view);
    texturedShader->loadLight(sun, 0);
    texturedShader->sky_color.load(skyColor);
    texturedShader->unbind();

    coloredShader->bind();
    coloredShader->view.load(*view);
    coloredShader->loadLight(sun, 0);
    coloredShader->sky_color.load(skyColor);
    *model_acacia_base = glm::scale(glm::mat4(1), glm::vec3(0.1f));
    *model_acacia_base = glm::translate(*model_acacia_base, glm::vec3(-5, -5, 5));
    coloredShader->model.load(*model_acacia_base);
    coloredShader->unbind();

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

    texturedShader->cleanup();
    coloredShader->cleanup();

    acacia_1->del();
    acacia_2->del();

    core::destroyDisplay();

    return 0;
}

void update(float delta)
{
    prevRectPos->x = rectPos->x;
    rectPos->x += 0.05;
}

void render(float alpha)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texturedShader->bind();

    if (core::displayResized())
    {
        *projection = glm::perspective(glm::radians(45.0f), (float) core::getDisplayWidth() / core::getDisplayHeight(), 0.1f, 100.0f);
        texturedShader->projection.load(*projection);

        glViewport(0, 0, core::getDisplayWidth(), core::getDisplayHeight());
    }

    float interp = core::lerp(rectPos->x, prevRectPos->x, alpha);

    acacia_3->bind();
    *model_acacia_base = glm::scale(glm::mat4(1), glm::vec3(0.25f));
    *model_acacia_base = glm::translate(*model_acacia_base, glm::vec3(interp, 0, 0));

    texturedShader->model.load(*model_acacia_base);
    //glDrawArrays(GL_TRIANGLES, 0, acacia_3->getVerticesLength());
    acacia_3->unbind();

    acacia_2->bind();
    *model_acacia_translated = glm::translate(*model_acacia_base, glm::vec3(-15, 5, 0));
    *model_acacia_translated = glm::rotate(*model_acacia_translated, glm::radians(interp) * -10, glm::vec3(0, 1, 0));
    texturedShader->model.load(*model_acacia_translated);
    //glDrawArrays(GL_TRIANGLES, 0, acacia_2->getVerticesLength());
    acacia_2->unbind();

    acacia_1->bind();
    *model_acacia_translated = glm::translate(*model_acacia_base, glm::vec3(15, -10, 0));
    *model_acacia_translated = glm::rotate(*model_acacia_translated, glm::radians(interp) * 10, glm::vec3(0, 1, 0));
    texturedShader->model.load(*model_acacia_translated);
    //glDrawArrays(GL_TRIANGLES, 0, acacia_1->getVerticesLength());
    acacia_1->unbind();

    texturedShader->unbind();

    coloredShader->bind();

    if (core::displayResized())
    {
        coloredShader->projection.load(*projection);
    }

    for (IndexedStaticModel model : terrain->models)
    {
        model.bind();
        glDrawElements(GL_TRIANGLES, model.getIndicesLength(), GL_UNSIGNED_INT, nullptr);
        model.unbind();
    }

    coloredShader->unbind();


    core::updateDisplay();
}