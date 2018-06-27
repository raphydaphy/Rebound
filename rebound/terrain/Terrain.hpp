#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include "../../engine/scene/Model.hpp"
#include <random>
#include <memory>
#include "../../engine/core/util.hpp"
#include "../../engine/core/loader.hpp"
#include "Biome.hpp"

struct TerrainVoxel
{
    TerrainVoxel(float density, Biome biome, float biomeEdge);
    float density;
    Biome biome;
    float biomeEdge;
};

class Terrain
{
public:
    Terrain(int gridX, int gridY, int gridZ);
    static const unsigned int size = 33;
    std::vector<ColoredStaticModel> models;
    float x, y, z;
private:
    float genBiomeDensity(int x, int z, int octaves, float scale, float persistance, float lacunarity, std::vector<glm::vec2> octaveOffsets);
    std::vector<ColoredModelData> generateModelData();
    std::vector<std::vector<std::vector<TerrainVoxel>>> voxels;
    std::vector<ColoredModelData> unprepared;
};

#endif