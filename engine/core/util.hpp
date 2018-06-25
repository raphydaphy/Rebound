#ifndef MATH_H
#define MATH_H

#include "../lib/FastNoise.hpp"

namespace core
{
    float lerp(float a, float b, float alpha);
    FastNoise getNoise();
    void initNoise(int seed);
}

#endif