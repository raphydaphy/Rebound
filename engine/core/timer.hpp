#ifndef TIMER_H
#define TIMER_H

#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>

namespace core
{
    void initTimer();

    float getDeltaTime();
    double getTime();

    void updateFPS();
    void updateTPS();
    void updateTimer();

    int getFPS();
    int getTPS();

    double getTimerLoopTime();
    void syncTimer(int targetFPS);
}

#endif