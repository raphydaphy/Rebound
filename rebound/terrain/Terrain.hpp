#ifndef TERRAIN_H
#define TERRAIN_H

#include "Biome.hpp"

struct TerrainVoxel
{
    TerrainVoxel(float density, Biome *biome, float biomeEdge);
    float density;
    Biome *biome;
    float biomeEdge;
};

#endif