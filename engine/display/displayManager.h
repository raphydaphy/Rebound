#ifndef LEARNCPP_DISPLAYMANAGER_H
#define LEARNCPP_DISPLAYMANAGER_H

#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace disp
{
    bool init();
    void destroy();
    bool open();
    void update();
    int getWidth();
    int getHeight();

    void errorCallback(int error, const char* description);
}

#endif
