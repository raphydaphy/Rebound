#ifndef MATH_H
#define MATH_H

#include "../lib/FastNoise.hpp"

namespace core
{
    float lerp(float a, float b, float alpha);
    float clamp(float value, float min, float max);
    FastNoise getNoise();
    void initNoise(int seed);
}

#endif