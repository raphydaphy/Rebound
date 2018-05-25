#include "timer.hpp"

namespace core
{
    double lastLoopTime;
    float timeCount = 0;

    int fps = 0;
    int fpsCount = 0;

    int tps = 0;
    int tpsCount = 0;

    int targetTPS = 20;

    float accumulator = 0;
    float interval = 1.0f / targetTPS;

    void initTimer()
    {
        lastLoopTime = glfwGetTime();
    }

    double getTime()
    {
        return glfwGetTime();
    }

    float getDeltaTime()
    {
        double time = getTime();
        auto delta = (float) (time - lastLoopTime);
        lastLoopTime = time;
        timeCount += delta;
        return delta;
    }

    float getAlphaTime()
    {
        return accumulator / interval;
    }

    void updateFPS()
    {
        fpsCount++;

        if (timeCount > 1)
        {
            fps = fpsCount;
            fpsCount = 0;

            tps = tpsCount;
            tpsCount = 0;

            timeCount -= 1;

            std::cout << "FPS: " << getFPS() << " TPS: " << getTPS() << std::endl;
        }

        accumulator += getDeltaTime();
    }

    void updateTPS()
    {
        tpsCount++;
        accumulator -= interval;
    }

    int getFPS()
    {
        return fps > 0 ? fps : fpsCount;
    }

    int getTPS()
    {
        return tps > 0 ? tps : tpsCount;
    }

    int getTargetTPS()
    {
        return targetTPS;
    }

    bool shouldTick()
    {
        return accumulator >= interval;
    }
}