#include "util.hpp"
#include "../lib/OpenSimplexNoise.hpp"

class GlobalRandoms
{
public:
    static GlobalRandoms &get()
    {
        static GlobalRandoms data;
        return data;
    }
private:
    GlobalRandoms() = default;
public:
    OpenSimplexNoise noise;
    std::mt19937 rand;
};

namespace core
{
    float lerp(float a, float b, float alpha)
    {
        return a + alpha * (b - a);
    }

    glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float alpha)
    {
        return glm::vec3(lerp(a.x, b.x, alpha), lerp(a.y, b.y, alpha), lerp(a.z, b.z, alpha));
    }

    float clamp(float value, float min, float max)
    {
        if (value > max) return max;
        else if (value < min) return min;
        return value;
    }

    void initSeed(int seed)
    {
        GlobalRandoms::get().noise = OpenSimplexNoise(seed);
        GlobalRandoms::get().rand = std::mt19937(seed);
    }

    float simplex(double a, double b)
    {
        return (float)GlobalRandoms::get().noise.Evaluate(a, b);
    }

    float simplex(double a, double b, double c)
    {
        return (float)GlobalRandoms::get().noise.Evaluate(a, b, c);
    }

    float simplex(double a, double b, double c, double d)
    {
        return (float)GlobalRandoms::get().noise.Evaluate(a, b, c, d);
    }

    int randomInt(int min, int max)
    {
        auto rnd = std::uniform_int_distribution<int>(min, max);
        return rnd(GlobalRandoms::get().rand);
    }

    float randomFloat(float min, float max)
    {
        auto rnd = std::uniform_real_distribution<float>(min, max);
        return rnd(GlobalRandoms::get().rand);
    }
}