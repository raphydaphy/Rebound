#ifndef REBOUND_MAIN_H
#define REBOUND_MAIN_H

#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/core/display.hpp"
#include "engine/core/timer.hpp"
#include "engine/gl/VertexArray.hpp"
#include "engine/core/loader.hpp"
#include "engine/lib/pico.hpp"
#include "engine/shader/impl/StaticShader.hpp"
#include "engine/scene/Model.hpp"
#include "engine/scene/Texture.hpp"
#include "engine/scene/Light.hpp"
#include "engine/core/util.hpp"
#include "rebound/terrain/Biome.hpp"
#include "rebound/terrain/Terrain.hpp"
#include "rebound/res/OBJModels.hpp"

void update(float delta);
void render(float alpha);

#endif
