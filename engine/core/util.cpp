#include "util.hpp"

class GlobalNoise
{
public:
    GlobalNoise() = default;
    FastNoise noise;
};

static constexpr GlobalNoise globalNoise;

namespace core
{
    float lerp(float a, float b, float alpha)
    {
        return a - alpha * (b - a);
    }

    FastNoise getNoise()
    {
        return globalNoise.noise;
    }

    void initNoise(int seed)
    {
        globalNoise.noise = FastNoise(seed);
    }
}