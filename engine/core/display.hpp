#ifndef LEARNCPP_DISPLAYMANAGER_H
#define LEARNCPP_DISPLAYMANAGER_H

#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace core
{
    bool initDisplay(const char *name);
    void destroyDisplay();

    bool displayOpen();
    bool displayResized();

    void updateDisplay();

    int getDisplayWidth();
    int getDisplayHeight();

    void errorCallback(int error, const char* description);
}

#endif
