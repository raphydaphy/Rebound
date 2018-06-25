#include "Biome.hpp"
#include "Terrain.hpp"

int lastBiomeID = 0;
int lastRegionID = 0;

//std::map<int, Biome> biomes;
//std::map<int, BiomeRegion> regions;

BiomeRegion::BiomeRegion(std::string name, float maxHeight, float r, float g, float b)
{
    this->name = std::move(name);
    this->maxHeight = maxHeight;
    this->color = glm::vec3(r, g, b);

    this->id = lastRegionID++;

   // regions.insert(std::pair<int, BiomeRegion>(this->id, *this));
}

BiomeRegion *BiomeRegion::getByID(int id)
{
    /*if (regions.find(id) != regions.end())
    {
        return &regions[id];
    }*/
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

    this->regions = std::vector<BiomeRegion>(regions);

    this->id = lastBiomeID++;

    //biomes.insert(std::pair<int, Biome>(this->id, *this));
}

Biome *Biome::getByID(int id)
{
    /*if (biomes.find(id) != biomes.end())
    {
        return &biomes[id];
    }*/
    return nullptr;
}


int Biome::getID()
{
    return this->id;
}

float Biome::genTerrainDensity(int x, int y, int z, int octaves, float scale, float persistance, float lacunarity,
                               float baseHeight, std::vector<glm::vec3> octaveOffsets)
{
    float density = getBaseDensity(x, y, z);
    float halfSize = Terrain::size / 2.0f;

    float amplitude = 2;
    float frequency = 1.5f;

    for (int octave = 0; octave < octaves; octave++)
    {
        float sampleX = (x - halfSize + octaveOffsets[octave].x) / scale * frequency;
        float sampleY = (y - halfSize + octaveOffsets[octave].y) / scale * frequency;
        float sampleZ = (z - halfSize + octaveOffsets[octave].z) / scale * frequency;

        float noiseValue = evaulateOctave(sampleX, sampleY, sampleZ);

        density += noiseValue * amplitude;

        amplitude *= persistance;
        frequency *= lacunarity;
    }

    return evaulateNoise(x, y, z, density, halfSize);
}

float Biome::evaulateOctave(float sampleX, float sampleY, float sampleZ)
{
    // TODO: this line

    return (float)core::getNoise().GetSimplex(sampleX, sampleY, sampleZ) * 2 - 1;
}

float Biome::evaulateNoise(int x, int y, int z, float density, float halfSize)
{
    return density * halfSize;
}

float Biome::getBaseDensity(int x, int y, int z)
{
    return -y / 2 + baseHeight;
}
