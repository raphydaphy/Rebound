#include "Terrain.hpp"

TerrainVoxel::TerrainVoxel(float density, Biome *biome, float biomeEdge)
{
    this->density = density;
    this->biome = biome;
    this->biomeEdge = biomeEdge;
}
