#include "main.hpp"

TexturedStaticModel *acacia_1;
TexturedStaticModel *acacia_2;
TexturedStaticModel *acacia_3;

StaticTexturedShader *texturedShader;
StaticColoredShader *coloredShader;

std::vector<Terrain> terrains;

glm::mat4 *projection;
glm::mat4 *view;

glm::vec3 *playerPos;
glm::vec3 *prevPlayerPos;

// TODO: better system for this
bool preparingTerrain = false;

static glm::mat4 smol = glm::scale(glm::mat4(1), glm::vec3(0.7f));

int main()
{
    if (!core::initDisplay("Rebound")) return 1;

    core::initTimer();
    core::setResourceDirectory("../rebound/res/");
    core::initSeed(0);

    biomes::init();

    glm::vec3 skyColor(227 / 256.0f, 168 / 256.0f, 87 / 256.0f);

    // TODO: improve rendering system
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(skyColor.x, skyColor.y, skyColor.z, 1);

    acacia_1 = new TexturedStaticModel("model/acacia_tree_1");
    acacia_2 = new TexturedStaticModel("model/acacia_tree_2");
    acacia_3 = new TexturedStaticModel("model/acacia_tree_3");

    for (int radius = 1; radius < 8; radius++)
    {
        for (int ix = -radius; ix < radius; ix++)
        {
            for (int iz = -radius; iz < radius; iz++)
            {
                bool done = false;
                for (Terrain &terrain : terrains)
                {
                    if (terrain.getGridX() == ix && terrain.getGridY() == 0 && terrain.getGridZ() == iz)
                    {
                        done = true;
                        break;
                    }
                }
                if (!done)
                {
                    terrains.emplace_back(ix, 0, iz);
                }
            }
        }
    }

    texturedShader = new StaticTexturedShader();
    coloredShader = new StaticColoredShader();

    Texture atlas = Texture("texture/atlas");
    atlas.bind();

    projection = new glm::mat4();

    view = new glm::mat4();

    float sunBrightness = 1;
    Light sun(glm::vec3(40000, 50000, 40000), glm::vec3(sunBrightness, sunBrightness, sunBrightness));

    playerPos = new glm::vec3(0, 10, 30);
    prevPlayerPos = new glm::vec3(*playerPos);

    texturedShader->bind();
    texturedShader->loadLight(sun, 0);
    texturedShader->sky_color.load(skyColor);
    texturedShader->unbind();

    coloredShader->bind();
    coloredShader->loadLight(sun, 0);
    coloredShader->sky_color.load(skyColor);
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
    acacia_3->del();

    for (auto &terrain : terrains)
    {
        terrain.del();
    }

    core::destroyDisplay();

    return 0;
}

void update(float delta)
{
    *prevPlayerPos = glm::vec3(*playerPos);

    float speed = 2;
    // TODO: better input system
    if (core::getKey(GLFW_KEY_W))
    {
        playerPos->z -= speed;
    }
    if (core::getKey(GLFW_KEY_S))
    {
        playerPos->z += speed;
    }
    if (core::getKey(GLFW_KEY_A))
    {
        playerPos->x -= speed;
    }
    if (core::getKey(GLFW_KEY_D))
    {
        playerPos->x += speed;
    }
    if (core::getKey(GLFW_KEY_SPACE))
    {
        playerPos->y += speed;
    }
    if (core::getKey(GLFW_KEY_LEFT_SHIFT))
    {
        playerPos->y -= speed;
    }

    for (auto &terrain : terrains)
    {
        terrain.update();

        if (!preparingTerrain && !terrain.generating && !terrain.generated)
        {
            std::cout << "started making a terrain" << std::endl;
            terrain.generating = true;
            preparingTerrain = true;
            std::thread t(&Terrain::generateModelData, &terrain);
            t.detach();
        }
        else if (preparingTerrain && terrain.generating && !terrain.generated && terrain.prepared())
        {
            std::cout << "finished making a terrain" << std::endl;
            terrain.generated = true;
            preparingTerrain = false;
        }
    }

}

void render(float alpha)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // TODO: better view matrix creation and updating
    glm::vec3 player = core::lerp(*prevPlayerPos, *playerPos, alpha);
    *view = glm::rotate(glm::mat4(1), glm::radians(15.0f), glm::vec3(1, 0, 0)); //pitch
    *view = glm::translate(*view, -player);


    texturedShader->bind();
    texturedShader->view.load(*view);

    if (core::displayResized() && core::getDisplayWidth() > 0 && core::getDisplayHeight() > 0)
    {
        *projection = glm::perspective(glm::radians(45.0f), (float) core::getDisplayWidth() / core::getDisplayHeight(), 0.1f, 200.0f);
        texturedShader->projection.load(*projection);

        glViewport(0, 0, core::getDisplayWidth(), core::getDisplayHeight());
    }

    acacia_2->bind();
    glm::mat4 model1 = glm::translate(smol, glm::vec3(-15, -0.5f, 13));
    texturedShader->model.load(model1);
    glDrawArrays(GL_TRIANGLES, 0, acacia_2->getVerticesLength());
    acacia_2->unbind();

    acacia_3->bind();
    glm::mat4 model2 = glm::translate(smol, glm::vec3(14.5f, 3, 43));
    texturedShader->model.load(model2);
    glDrawArrays(GL_TRIANGLES, 0, acacia_3->getVerticesLength());
    acacia_3->unbind();

    acacia_1->bind();
    glm::mat4 model3 = glm::translate(smol, glm::vec3(3, -1, 15));
    texturedShader->model.load(model3);
    glDrawArrays(GL_TRIANGLES, 0, acacia_1->getVerticesLength());
    acacia_1->unbind();

    texturedShader->unbind();

    coloredShader->bind();
    coloredShader->view.load(*view);

    if (core::displayResized())
    {
        coloredShader->projection.load(*projection);
    }

    for (auto &terrain : terrains)
    {
        if (terrain.prepared())
        {
            glm::mat4 terrainModel = glm::translate(glm::mat4(1), glm::vec3(terrain.x - 15, terrain.y - 15, terrain.z));
            coloredShader->model.load(terrainModel);
            for (ColoredStaticModel model : terrain.models)
            {
                model.bind();
                glDrawArrays(GL_TRIANGLES, 0, model.getVerticesLength());
                model.unbind();
            }
        }
    }

    coloredShader->unbind();

    core::updateDisplay();
}