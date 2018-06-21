#ifndef BIOME_H
#define BIOME_H

#include <string>
#include <glm/vec3.hpp>
#include <utility>
#include <initializer_list>
#include <vector>
#include <map>

struct BiomeRegion
{
    BiomeRegion(std::string name, float maxHeight, float r, float g, float b);
    BiomeRegion *getByID(int id);
    std::string name;
    float maxHeight;
    glm::vec3 color;

    int id;
};
class Biome
{
public:
    Biome(float maxHeight, float heightMultiplier, float baseHeight, int noiseOctaves, float noiseScale, float noisePersistance, float noiseLacunarity, std::initializer_list<BiomeRegion> regions);
    Biome *getByID(int id);
    int getID();
private:
    int id;

    float maxHeight;
    float heightMultiplier;
    float baseHeight;

    int noiseOctaves;
    float noiseScale;
    float noisePersistance;
    float noiseLacunarity;

    std::vector<BiomeRegion> regions;
};

#endif