#include "timer.hpp"

namespace core
{
    double lastLoopTime;
    float timeCount = 0;

    int fps = 0;
    int fpsCount = 0;

    int tps = 0;
    int tpsCount = 0;

    void initTimer()
    {
        lastLoopTime = glfwGetTime();
    }

    float getDeltaTime()
    {
        double time = getTime();
        auto delta = (float) (time - lastLoopTime);
        lastLoopTime = time;
        timeCount += delta;
        return delta;
    }

    double getTime()
    {
        return glfwGetTime();
    }

    void updateFPS()
    {
        fpsCount++;
    }

    void updateTPS()
    {
        tpsCount++;
    }

    void updateTimer()
    {
        if (timeCount > 1)
        {
            fps = fpsCount;
            fpsCount = 0;

            tps = tpsCount;
            tpsCount = 0;

            timeCount -= 1;

            std::cout << "FPS: " << getFPS() << " TPS: " << getTPS();
        }
    }

    int getFPS()
    {
        return fps > 0 ? fps : fpsCount;
    }

    int getTPS()
    {
        return tps > 0 ? tps : tpsCount;
    }

    double getTimerLoopTime()
    {
        return lastLoopTime;
    }

    void syncTimer(int targetFPS)
    {
        double now = getTime();
        float target = 1.0f / targetFPS;

        while (now - lastLoopTime < target);
        {
            std::this_thread::yield();
            //std::this_thread::sleep_for(std::chrono::milliseconds(1));
            now = getTime();
        }
    }
}