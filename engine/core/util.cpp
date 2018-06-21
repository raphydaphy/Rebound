#include "util.hpp"

OpenSimplexNoise *noise;

namespace core
{
    float lerp(float a, float b, float alpha)
    {
        return a - alpha * (b - a);
    }

    OpenSimplexNoise getNoise()
    {
        return *noise;
    }

    void initNoise(int seed)
    {
        noise = new OpenSimplexNoise(seed);
    }
}