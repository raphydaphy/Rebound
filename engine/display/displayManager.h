#ifndef LEARNCPP_DISPLAYMANAGER_H
#define LEARNCPP_DISPLAYMANAGER_H

#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace disp
{
    bool init();
    void destroy();
    bool open();
    void update();
}

#endif