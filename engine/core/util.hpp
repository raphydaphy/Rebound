#ifndef MATH_H
#define MATH_H

#include "../lib/OpenSimplexNoise.hpp"

namespace core
{
    float lerp(float a, float b, float alpha);
    OpenSimplexNoise getNoise();
    void initNoise(int seed);
}

#endif