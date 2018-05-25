#ifndef TIMER_H
#define TIMER_H

#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>
#include <iostream>

namespace core
{
    void initTimer();

    double getTime();
    float getDeltaTime();
    float getAlphaTime();

    void updateFPS();
    void updateTPS();

    int getFPS();
    int getTPS();
    int getTargetTPS();

    bool shouldTick();
}

#endif