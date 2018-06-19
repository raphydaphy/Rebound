#include "Biome.hpp"

int lastBiomeID = 0;
int lastRegionID = 0;

std::map<int, Biome> biomes;
std::map<int, BiomeRegion> regions;

BiomeRegion::BiomeRegion(std::string name, float maxHeight, float r, float g, float b)
{
    this->name = std::move(name);
    this->maxHeight = maxHeight;
    this->color = glm::vec3(r, g, b);

    this->id = lastRegionID++;

    regions.insert(std::pair<int, BiomeRegion>(this->id, *this));
}

BiomeRegion BiomeRegion::getByID(int id)
{
    if (regions.find(id) != regions.end())
    {
        return regions[id];
    }
    return nullptr;
}

Biome::Biome(float maxHeight, float heightMultiplier, float baseHeight, int noiseOctaves, float noiseScale,
             float noisePersistance, float noiseLacunarity, std::initializer_list<BiomeRegion> regions)
{
    this->maxHeight = maxHeight;
    this->heightMultiplier = heightMultiplier;
    this->baseHeight = baseHeight;
    this->noiseOctaves = noiseOctaves;
    this->noiseScale = noiseScale;
    this->noisePersistance = noisePersistance;
    this->noiseLacunarity = noiseLacunarity;

    this->regions = std::vector(regions);

    this->id = lastBiomeID++;

    biomes.insert(std::pair<int, Biome>(this->id, *this));
}

Biome Biome::getByID(int id)
{
    if (biomes.find(id) != biomes.end())
    {
        return biomes[id];
    }
    return nullptr;
}


int Biome::getID()
{
    return this->id;
}