#include "Biome.hpp"

int lastID = 0;

Biome::Biome(float maxHeight, float heightMultiplier, float baseHeight, int noiseOctaves, float noiseScale,
             float noisePersistance, float noiseLacunarity)
{
    this->maxHeight = maxHeight;
    this->heightMultiplier = heightMultiplier;
    this->baseHeight = baseHeight;
    this->noiseOctaves = noiseOctaves;
    this->noiseScale = noiseScale;
    this->noisePersistance = noisePersistance;
    this->noiseLacunarity = noiseLacunarity;

    this->id = lastID++;
}

int Biome::getID()
{
    return this->id;
}
