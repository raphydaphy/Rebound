#ifndef BIOME_H
#define BIOME_H

#include <string>
#include <glm/vec3.hpp>
#include <utility>
#include <initializer_list>
#include <vector>
#include <map>
#include "../../engine/core/util.hpp"
#include <memory>

struct BiomeRegion
{
    BiomeRegion(std::string name, float maxHeight, float r, float g, float b);
    BiomeRegion getByID(int id);
    std::string name;
    float maxHeight;
    glm::vec3 color;

    int id;
};

class Biome
{
public:
    Biome(float maxHeight, float heightMultiplier, float baseHeight, int noiseOctaves, float noiseScale, float noisePersistance, float noiseLacunarity, std::initializer_list<BiomeRegion> regions);
    static Biome getByID(int id);
    static Biome getByHeight(float height);
    int getID();
    virtual float genTerrainDensity(int x, int y, int z, int octaves, float scale, float persistance, float lacunarity, float baseHeight, std::vector<glm::vec3> octaveOffsets);
    bool operator==(const Biome &rhs);

    int id;

    float maxHeight;
    float heightMultiplier;
    float baseHeight;

    int noiseOctaves;
    float noiseScale;
    float noisePersistance;
    float noiseLacunarity;
protected:
    virtual float evaulateOctave(float sampleX, float sampleY, float sampleZ);
    virtual float evaulateNoise(int x, int y, int z, float density, float halfSize);
    virtual float getBaseDensity(int x, int y, int z);
private:
    std::vector<BiomeRegion> regions;
};

class ForestBiome : public Biome
{
public:
    ForestBiome();
};

class DesertBiome : public Biome
{
public:
    DesertBiome();
};

namespace biomes
{
    static constexpr ForestBiome forest();
    static constexpr DesertBiome desert();

    std::shared_ptr<Biome> getHighestBiome();
    int getHighestOctaveCount();
}
#endif