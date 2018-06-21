#ifndef LEARNCPP_MAIN_H
#define LEARNCPP_MAIN_H

#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/core/display.hpp"
#include "engine/core/timer.hpp"
#include "engine/gl/VertexArray.hpp"
#include "engine/core/loader.hpp"
#include "engine/lib/pico.hpp"
#include "engine/shader/impl/StaticObjectShader.hpp"
#include "engine/scene/Model.hpp"
#include "engine/scene/Texture.hpp"
#include "engine/scene/Light.hpp"

void update(float delta);
void render(float alpha);

#endif
