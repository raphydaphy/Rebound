#include "util.hpp"

FastNoise *noise;

namespace core
{
    float lerp(float a, float b, float alpha)
    {
        return a - alpha * (b - a);
    }

    FastNoise getNoise()
    {
        return *noise;
    }

    void initNoise(int seed)
    {
        noise = new FastNoise(seed);
    }
}