#include "util.hpp"

class GlobalNoise
{
public:
    static GlobalNoise &get()
    {
        static GlobalNoise data;
        return data;
    }
private:
    GlobalNoise() = default;
public:
    FastNoise noise;
};

namespace core
{
    float lerp(float a, float b, float alpha)
    {
        return a - alpha * (b - a);
    }

    FastNoise getNoise()
    {
        return GlobalNoise::get().noise;
    }

    void initNoise(int seed)
    {
        GlobalNoise::get().noise = FastNoise(seed);
    }
}