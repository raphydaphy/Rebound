#ifndef MATH_H
#define MATH_H

#include "../lib/FastNoise.hpp"
#include <random>

namespace core
{
    float lerp(float a, float b, float alpha);
    float clamp(float value, float min, float max);
    float simplex(float a, float b);
    float simplex(float a, float b, float c);
    float simplex(float a, float b, float c, float d);
    int randomInt(int min, int max);
    float randomFloat(float min, float max);
    void initSeed(int seed);
}

#endif