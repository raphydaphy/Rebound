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
    TerrainVoxel(float density, Biome *biome, float biomeEdge);
    float density;
    Biome *biome;
    float biomeEdge;
};

class Terrain
{
public:
    static const int size = 33;
private:
    float genBiomeDensity(int x, int z, int octaves, float scale, float persistance, float lacunarity, std::vector<glm::vec2> octaveOffsets);
    std::vector<ColoredModelData> generateModelData();
    std::vector<TerrainVoxel> voxels;
    std::vector<ColoredStaticModel> models;
    std::vector<ColoredModelData> unprepared;
    float x, y, z;
};

#endif