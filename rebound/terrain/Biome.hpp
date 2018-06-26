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
    BiomeRegion getByID(unsigned int id);
    std::string name;
    float maxHeight;
    glm::vec3 color;

    unsigned int id;
};

class Biome
{
public:
    Biome(float maxHeight, float heightMultiplier, float baseHeight, unsigned int noiseOctaves, float noiseScale, float noisePersistance, float noiseLacunarity, std::initializer_list<BiomeRegion> regions);
    virtual float genTerrainDensity(int x, int y, int z, std::vector<glm::vec3> octaveOffsets);
    bool operator==(const Biome &rhs);

    BiomeRegion getRegionFromID(unsigned int id);
    BiomeRegion getRegionFromHeight(float height);

    unsigned int id;
    float heightMultiplier;
    float maxHeight;
protected:
    virtual float evaulateOctave(float sampleX, float sampleY, float sampleZ);
    virtual float evaulateNoise(int x, int y, int z, float density, float halfSize);
    virtual float getBaseDensity(int x, int y, int z);

    float baseHeight;

    unsigned int noiseOctaves;
    float noiseScale;
    float noisePersistance;
    float noiseLacunarity;
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
    std::shared_ptr<Biome> getHighestBiome();
    int getHighestOctaveCount();

    Biome getByID(unsigned int id);
    Biome getByHeight(float height);

    void init();
}
#endif