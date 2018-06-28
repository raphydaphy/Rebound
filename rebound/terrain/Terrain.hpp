#ifndef REBOUND_TERRAIN_H
#define REBOUND_TERRAIN_H

#include <vector>
#include "../../engine/scene/Model.hpp"
#include <random>
#include <memory>
#include "../../engine/core/util.hpp"
#include "../../engine/core/loader.hpp"
#include "Biome.hpp"
#include <thread>
#include <utility>

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
    static const unsigned int size = 5;
    std::vector<ColoredStaticModel> models;
    int x, y, z;
    void del();
    void update();
    bool prepared();
    void generateModelData();
    bool generating = false;
    bool generated = false;
    int getGridX();
    int getGridY();
    int getGridZ();
private:
    float genBiomeDensity(int x, int z, int octaves, float scale, float persistance, float lacunarity, std::vector<glm::vec2> octaveOffsets);
    std::vector<glm::vec3> genTerrainOffsets(int octaves, glm::vec3 offset);
    std::vector<glm::vec2> genBiomeOffsets(int octaves, glm::vec3 offset);
    std::vector<std::vector<std::vector<TerrainVoxel>>> voxels;
    std::vector<ColoredModelData> unprepared;
    std::mt19937 rand;
};

#endif