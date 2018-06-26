#ifndef MATH_H
#define MATH_H

#include <random>
#include <glm/gtc/matrix_transform.hpp>

namespace core
{
    float lerp(float a, float b, float alpha);
    glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float alpha);
    float clamp(float value, float min, float max);
    float simplex(double a, double b);
    float simplex(double a, double b, double c);
    float simplex(double a, double b, double c, double d);
    int randomInt(int min, int max);
    float randomFloat(float min, float max);
    void initSeed(int seed);
}

#endif