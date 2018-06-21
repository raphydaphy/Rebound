#ifndef TERRAIN_H
#define TERRAIN_H

#include "Biome.hpp"
#include <vector>
#include "../../engine/scene/Model.hpp"

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
    std::vector<ColoredModelData> generateModelData();
    std::vector<TerrainVoxel> voxels;
    std::vector<ColoredStaticModel> models;
    std::vector<ColoredModelData> unprepared;
    float x, y, z;
};

#endif